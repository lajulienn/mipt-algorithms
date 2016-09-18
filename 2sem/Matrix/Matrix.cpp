#include "Matrix.h"
#include <iostream>

Matrix::Matrix(int h, int w) {
	height_ = h;
	width_ = w;
	data_ = new int[h * w];
	memset(data_, 0, h * w * sizeof(data_[0]));
}

Matrix::Matrix(const Matrix &m) {
	height_ = m.height_;
	width_ = m.width_;
	data_ = new int[height_ * width_];
	memcpy(data_, m.data_, height_ * width_ * sizeof(data_[0]));
}

Matrix::~Matrix() {
	delete[] data_;
}

std::ostream& operator<<(std::ostream &s, const Matrix &m) {
	for (int i = 0; i < m.height_; ++i) {
		for (int j = 0; j < m.width_; ++j) 
			std::cout << m.data_[i * m.width_ + j] << ' ';
		std::cout << std::endl;
	}
	std::cout << std::endl;
	return s;
}
int & Matrix::operator() (int i, int j) {
	if (i >= height_ || j >= width_) 
		throw std::runtime_error("Invalid index");
	return data_[i * width_ + j];
}

const int Matrix::operator() (int i, int j) const {
	if (i >= height_ || j >= width_)
		throw std::runtime_error("Invalid index");
	return data_[i * width_ + j];
}

Matrix & Matrix::operator=(const Matrix &m) {
	if (height_ != m.height_ || width_ != m.width_) {
		delete[] data_;
		data_ = new int[m.height_ * m.width_];
	}
	height_ = m.height_;
	width_ = m.width_;
	memcpy(data_, m.data_, height_ * width_ * sizeof(data_[0]));
	return *this;
}

Matrix &Matrix::operator+=(const Matrix &m) {
	if (height_ != m.height_ || width_ != m.width_) {
		throw std::runtime_error("Incompatible argument dimensions");
	}
	for (int i = 0; i < height_* width_; ++i) {
		data_[i] += m.data_[i];
	}
	return *this;
}

Matrix operator+(const Matrix &s, const Matrix &m) {
	if (s.height_ != m.height_ || s.width_ != m.width_) {
		throw std::runtime_error("Incompatible argument dimensions");
	}
	Matrix res(s);
	res += m;
	return res;
}

Matrix Matrix::operator*(int val) {
	for (int i = 0; i < height_* width_; ++i) {
		data_[i] *= val;
	}
	return *this;
}

Matrix operator*(int val, Matrix &m) {
	return m * val;
}

Matrix &Matrix::operator*=(const Matrix &m) {
	*this = *this * m;
	return *this;
}

Matrix operator*(const Matrix &m1, const Matrix &m2) {
	if (m1.width() != m2.height()) {
		throw std::runtime_error("Incompatible argument dimensions");
	}
	Matrix result(m1.height(), m2.width());

	for (int i = 0; i < m1.height(); ++i) {
		for (int j = 0; j < m2.width(); ++j) {
			for (int k = 0; k < m1.width(); ++k) {
				result(i, j) += m1(i, k) * m2(k, j);
			}
		}
	}

	return result;
}

void Matrix::transpose() {
	Matrix result(width_, height_);
	for (int i = 0; i < result.height(); ++i) {
		for (int j = 0; j < result.width(); ++j) {
			result(i, j) = (j, i);
		}
	}
	*this = result;
}