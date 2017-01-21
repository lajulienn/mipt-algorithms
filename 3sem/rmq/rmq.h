/**
 * @author Julia Ivanova
 */

#ifndef RMQ_RMQ_H
#define RMQ_RMQ_H

#include <vector>

class Rmq {
 public:
  Rmq(const std::vector<int> &array);
  int GetSecondElement(int from, int to);
 private:
  struct Element {
    Element(int value, int position);
    int value_;
    int position_;
  };
  std::pair<Rmq::Element, Rmq::Element> Compare(std::pair<Element, Element> a, std::pair<Element, Element> b);

  std::vector<std::vector<std::pair<Element, Element>>> table;
  std::vector<int> logarithm;
};

#endif //RMQ_RMQ_H
