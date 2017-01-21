/**
 * @author Julia Ivanova
 */

#include "rmq.h"

Rmq::Element::Element(int value = 0, int position = 0)
    : value_(value), position_(position) {}

Rmq::Rmq(const std::vector<int> &array) : logarithm(array.size() + 1) {
  table.emplace_back();
  table.emplace_back(array.size() - 1);
  for (int i = 0; i < array.size() - 1; ++i) {
    if (array[i] < array[i + 1]) {
      table.back()[i] = {Element(array[i], i), Element(array[i + 1], i + 1)};
    } else {
      table.back()[i] = {Element(array[i + 1], i + 1), Element(array[i], i)};
    }
  }
  int block_size = 2;
  while(block_size <= array.size() / 2 + array.size() % 2) {

    std::vector<std::pair<Element, Element>> next_level(table.back().size() - block_size);
    for(int i = 0; i < table.back().size() - block_size; ++i) {
      next_level[i] = Compare(table.back()[i], table.back()[i + block_size]);
    }
    table.push_back(std::move(next_level));
    block_size *= 2;
  }

  int log = 1;
  for (int x = 2; x <= array.size(); ++x) {
    if (1 << (log + 1) <= x) {
      ++log;
    }
    logarithm[x] = log;
  }
}

std::pair<Rmq::Element, Rmq::Element> Rmq::Compare(std::pair<Element, Element> a,
                                                   std::pair<Element, Element> b) {
  std::pair<Rmq::Element, Rmq::Element> result = std::pair<Rmq::Element, Rmq::Element>();
  if (a.first.value_ == b.first.value_) {
    if (a.first.position_ != b.first.position_) {
      result.first = Element(a.first.value_, a.first.position_);
      result.second = Element(a.first.value_ ,b.second.position_);
    } else {
      result.first = Element(a.first.value_, a.first.position_);
      if (a.second.value_ < b.second.value_) {
        result.second = Element(a.second.value_, a.second.position_);
      } else {
        result.second = Element(b.second.value_, b.second.position_);
      }
    }
  } else {
    if (a.first.value_ < b.first.value_) {
      result.first = Element(a.first.value_, a.first.position_);

      if (b.first.value_ < a.second.value_) {
        result.second = Element(b.first.value_, b.first.position_);
      } else {
        result.second = Element(a.second.value_, a.second.position_);
      }
    } else {
      result.first = Element(b.first.value_, b.first.position_);

      if (a.first.value_ < b.second.value_) {
        result.second = Element(a.first.value_, a.first.position_);
      } else {
        result.second = Element(b.second.value_, b.second.position_);
      }
    }
  }

  return result;
}

int Rmq::GetSecondElement(int from, int to) {
  int length = to - from + 1;
  int log = logarithm[length];
  std::pair<Rmq::Element, Rmq::Element> result;
  result = Compare(table[log][from], table[log][to - (1 << log) + 1]);
  return result.second.value_;
}