#pragma once
#include <iostream>

class Matrix {
public:
	Matrix(int, int);
	Matrix(const Matrix &);
	~Matrix();
	friend std::ostream& operator<<(std::ostream &s, const Matrix &m);
	int & operator() (int i, int j);
	const int operator() (int i, int j) const;
	int height() const { return height_; };
	int width() const { return width_; };
	Matrix & operator=(const Matrix &);
	Matrix &operator+=(const Matrix &);
	friend Matrix operator+(const Matrix &, const Matrix &);
	Matrix operator*(int);
	friend Matrix operator*(int val, const Matrix &);
	Matrix &operator*=(const Matrix &);
	void transpose();
private:
	int height_;
	int width_;
	int *data_;
};

std::ostream& operator<<(std::ostream &s, const Matrix &m);
Matrix operator*(int val, Matrix &);
Matrix operator+(const Matrix &, const Matrix &);
Matrix operator*(const Matrix &m1, const Matrix &m2);
