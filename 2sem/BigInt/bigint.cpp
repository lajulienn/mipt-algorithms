#include <iostream>
#include <algorithm>
#include "bigint.h"
#include <set>

void BigInt::scan() {
	std::string s;
	std::cin >> s;
	for (int i = s.size() - 1; i > 0; --i) {
		digits_.push_back(s[i] - '0');
	}
	if (s[0] == '-') {
		sign_ = -1;
	} else {
		digits_.push_back(s[0] - '0');
	}
}

void BigInt::print() const {
	if (sign_ == -1)
		std::cout << '-';
	for (int i = digits_.size() - 1; i >= 0; --i)
		std::cout << digits_[i];
	std::cout << std::endl;
}

BigInt BigInt::operator+(const BigInt &n2) {
	BigInt result;

	int max = std::max(digits_.size(), n2.digits_.size());
	int min = std::min(digits_.size(), n2.digits_.size());

	int i = 0, tmp = 0, value = 0;
	while (i < min) {
		value = digits_[i] + n2.digits_[i] + tmp;
		result.digits_.push_back(value % 10);
		tmp = value / 10;
		++i;
	}
	if (digits_.size() > n2.digits_.size()) {
		for (int i = min; i < max; ++i) {
			value = digits_[i] + tmp;
			result.digits_.push_back(value % 10);
			tmp = value / 10;
		}
	} else {
		for (int i = min; i < max; ++i) {
			value = n2.digits_[i] + tmp;
			result.digits_.push_back(value % 10);
			tmp = value / 10;
		}
	}
	if (tmp)
		result.digits_.push_back(tmp);

	result.sign_ = 1;

	return result;
}

BigInt BigInt::operator-(const BigInt &_n2) {
	BigInt result, n1, n2;
	if (*this == n2) {
		return BigInt(0);
	} else if (*this < n2) {
		result.sign_ = -1;
		n1 = _n2;
		n2 = *this;
	} else {
		n1 = *this;
		n2 = _n2;
	}

	int max = std::max(n1.digits_.size(), n2.digits_.size());
	int min = std::min(n1.digits_.size(), n2.digits_.size());

	int i = 0, value = 0, tmp = 0;
	while (i < min) {
		value = n1.digits_[i] - n2.digits_[i] + tmp;
		tmp = 0;
		if (value < 0) {
			value += 10;
			tmp = -1;
		}
		result.digits_.push_back(value);
		++i;
	}
	for (i = min; i < max; ++i) {
		value = n1.digits_[i] + tmp;
		tmp = 0;
		if (value < 0) {
			value += 10;
			tmp = -1;
		}
		result.digits_.push_back(value);
	}
	while (!result.digits_.back())
		result.digits_.pop_back();
	return result;
}

int cmp(const BigInt &n1, const BigInt &n2) {
	int result = 0;
	if (n1.digits_.size() > n2.digits_.size()) {
		return 1;
	} else if (n2.digits_.size() > n1.digits_.size()) {
		return -1;
	}
	int size = n1.digits_.size();
	for (int i = size - 1; i >= 0; --i) {
		if (n1.digits_[i] > n2.digits_[i]) {
			return 1;
		} else if (n2.digits_[i] > n1.digits_[i]) {
			return -1;
		}
	}
	return 0;
}

bool BigInt::operator<(const BigInt &n) const {
	return (cmp(*this, n) < 0);
}

bool BigInt::operator==(const BigInt &n) const {
	return (cmp(*this, n) == 0);
}

BigInt BigInt::operator*(const BigInt &_n2) {
	BigInt result, n1, n2, tmp;
	if ((this->digits_.size() == 1 && this->digits_[0] == 0) || (_n2.digits_.size() == 1 && _n2.digits_[0] == 0))
		return BigInt(0);
	if (*this < _n2) {
		n1 = _n2;
		n2 = *this;
	} else {
		n1 = *this;
		n2 = _n2;
	}

	for (int i = 0; i < n2.digits_.size(); ++i) {
		tmp = n1 * n2.digits_[i];
		for (int j = 0; j < i; ++j)
			tmp.shift();
		result = result + tmp;
	}
	return result;
}

void BigInt::shift() {
	digits_.insert(digits_.cbegin(), 0);
}

BigInt BigInt::operator*(int x) {
	BigInt result;
	int value = 0, tmp = 0;
	for (int i = 0; i < digits_.size(); ++i) {
		value = digits_[i] * x + tmp;
		result.digits_.push_back(value % 10);
		tmp = value / 10;
	}
	if (tmp)
		result.digits_.push_back(tmp);
	return result;
}

void scan(BigInt &n1, BigInt&n2) {
	std::string s;
	std::cin >> s;
	int i = s.length() - 1;
	while (s[i] != '/') {
		n2.digits_.push_back(s[i] - '0');
		--i;
 	}
	for (i -= 1; i >= 0; --i) {
		n1.digits_.push_back(s[i] - '0');
	}
}

//std::string operator/(const BigInt &_n1, const BigInt &n2) {
//	BigInt n1 = _n1;
//	std::string result;
//	BigInt result_int, result_frac, tmp;
//	std::set<int> remainders;
//
//	/*if (greater(n2, n1) > 0) {
//		result.push_back('0');
//	} else {
//		for (int i = 0; i < n2.digits_.size(); ++i)
//			tmp.digits_.push_back(n1.digits_[i]);
//		if (greater(n2, tmp) > 0) 
//			if (n2.digits_.size() == n1.digits_.size()) {
//				result_int = BigInt(0);
//			} else {
//				tmp.digits_.push_back(n1.digits_[n2.digits_.size()]);
//			}
//	}
//	
//	BigInt prev_result = n2;
//	BigInt curr_result;
//	for (int x = 2; x <= 9; ++x) {
//		curr_result = n1 * x;
//		if (greater(curr_result, tmp) >= 0)
//			result.push_back((char)(x + '0'));
//
//	}*/
//
//
//	int length = n1.digits_.size();
//	BigInt tmp;
//	for (int i = length - 1; i >= 0 && greater(n1, n2) >= 0; --i) {
//		tmp.digits_.insert(n1.digits_.cbegin(), n1.digits_[i]);
//		if (greater(tmp, n2) >= 0) {
//			BigInt prev_result = n2;
//			BigInt curr_result;
//			for (int x = 0; x < 10; ++x) { 
//				curr_result = n1 * x;
//				if (greater(curr_result, tmp) >= 0)
//					result.push_back((char)(x + '0'));
//			}
//		}
//	}
//
//}

