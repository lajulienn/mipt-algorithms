#include <iostream>
#include <ostream>
#include "Vector2D.h"

Vector2D::Vector2D(double x_, double y_) {
	x = x_;
	y = y_;
	std::cout << "Vector2D::Vector2D" << std::endl;
}

Vector2D::~Vector2D() {
	std::cout << "Vector2D::~Vector2D" << std::endl;
}

std::ostream& operator<<(std::ostream &s, const Vector2D &v) {
	s << "(" << v.x << "," << v.y << ")" << std::endl;
	return s;
}

Vector2D Vector2D::operator*(double k) const {
	return Vector2D(x * k, y * k);
}

Vector2D operator*(double k, const Vector2D &v) {
	return v * k;
}

Vector2D Vector2D::operator/(double k) {
	return Vector2D(x / k, y / k);
}

Vector2D Vector2D::operator+(const Vector2D &v) {
	return Vector2D(this->x + v.x, this->y + v.y);
}

Vector2D Vector2D::operator-(const Vector2D &v) {
	return Vector2D(this->x - v.x, this->y - v.y);
}

void Vector2D::operator+=(const Vector2D &v) {
	this->x += v.x;
	this->y += v.y;
}

void Vector2D::operator-=(const Vector2D &v) {
	this->x -= v.x;
	this->y -= v.y;
}

void Vector2D::operator*=(double k) {
	this->x *= k;
	this->y *= k;
}

void Vector2D::operator/=(double k) {
	this->x /= k;
	this->y /= k;
}

double Vector2D::operator*(const Vector2D &v) {
	return this->x * v.x +  this->y * v.y;
}

bool Vector2D::operator==(const Vector2D &v) {
	return (this->x == v.x) && (this->y == v.y);
}

bool Vector2D::operator!=(const Vector2D &v) {
	return (this->x != v.x) || (this->y != v.y);
}