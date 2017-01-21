#pragma once

struct Vector2D {
	double x, y;
	explicit Vector2D(double x_ = 0, double y_ = 0);
	Vector2D(const Vector2D &v);
	~Vector2D();
	Vector2D operator+(const Vector2D &);
	Vector2D operator-(const Vector2D &);
	double operator*(const Vector2D &);
	Vector2D operator*(double) const;
	Vector2D operator/(double);
	void operator+=(const Vector2D &);
	void operator-=(const Vector2D &);
	void operator*=(double);
	void operator/=(double);
	bool operator==(const Vector2D &);
	bool operator!=(const Vector2D &);
	double operator() () {
		return sqrt((*this) * (*this));
	}
};

std::ostream& operator<<(std::ostream &s, const Vector2D &v);

Vector2D operator*(double, const Vector2D &);