#include "MyString.h"
#include <iostream>
#include <istream>
#include <string>

const int INITIAL_CAPACITY = 10;

MyString::MyString(const MyString & s) {
	capacity = s.capacity;
	length = s.length;
	data = new char[capacity];
	memcpy(data, s.data, length * sizeof(data[0]));
}

MyString::~MyString() {
	delete[] data;
}

MyString::MyString(char c) {
	capacity = INITIAL_CAPACITY;
	length = 1;
	data = new char[capacity];
	data[0] = c;
}

MyString::MyString(int len) {
	length = capacity = len;
	data = new char[capacity];
}

MyString::MyString(const char *c) {
	capacity = length = strlen(c);
	if (!capacity)
		capacity = INITIAL_CAPACITY;
	data = new char[capacity];
	memcpy(data, c, length * sizeof(data[0]));
}

MyString & MyString::operator=(char c) {
	capacity_check(1);
	data[0] = c;
	length = 1;
	return *this;
}

MyString & MyString::operator=(const char *c) {
	length = strlen(c);
	capacity_check(length);
	memcpy(data, c, length * sizeof(data[0]));
	return *this;
}

MyString & MyString::operator=(const MyString &s) {
	if (&s == this)
		return *this;

	capacity = s.capacity;
	length = s.length;
	delete[] data;
	data = new char[capacity];
	memcpy(data, s.data, length * sizeof(data[0]));
	return *this;
}

MyString MyString::operator+(char c) const {
	MyString s = *this;
	s += c;
	return s;
}

MyString MyString::operator+(const char *c) const {
	MyString s = *this;
	s += c;
	return s;
}

MyString MyString::operator+(const MyString & s) const {
	MyString tmp = *this;
	tmp += s;
	return tmp;
}

char MyString::operator[](int i) const {
	return data[i];
}

char & MyString::operator[](int i) {
	return data[i];
}

void MyString::capacity_check(int new_length) {
	if (capacity >= new_length)
		return;
	while (capacity < new_length) {
		capacity *= 2;
	}
		char *new_data = new char[capacity];
		memcpy(new_data, data, length * sizeof(data[0]));
		delete data;
		data = new_data;
	
}

std::ostream& operator<<(std::ostream &s, const MyString &c) {
	for (int i = 0; i < c.length; ++i) {
		s << c[i];
	}
	s << std::endl;
	return s;
}

std::istream& operator>>(std::istream &s, MyString &c) {
	std::string str;
	s >> str;
	c = str.c_str();
	return s;
}

MyString operator+(char c, const MyString &s) 
{
	int new_length = s.length + 1;
	MyString result(new_length);
	result.data[0] = c;
	memcpy(result.data + 1, s.data, s.length);
	return result;
}

MyString operator+(const char *c, const MyString &s) {
	int new_length = s.length + strlen(c);
	MyString result(new_length);
	memcpy(result.data, c, strlen(c));
	memcpy(result.data + strlen(c), s.data, s.length);
	return result;
}

int MyString::get_length() const {
	return length;
}

MyString & MyString::operator+=(const MyString &s) {
	capacity_check(length + s.length);
	memcpy(data + length, s.data, s.length * sizeof(data[0]));
	length += s.length;
	return *this;
}

MyString & MyString::operator+=(const char *s) {
	int add_length = strlen(s);
	capacity_check(length + add_length);
	memcpy(data + length, s, add_length * sizeof(data[0]));
	length += add_length;
	return *this;
}

MyString & MyString::operator+=(char c) {
	int add_length = 1;
	capacity_check(length + add_length);
	data[length] = c;
	++length;
	return *this;
}

void MyString::reverse() {
	int i = 0;
	int j = length - 1;
	while (i < j) {
		char tmp;
		tmp = data[i];
		data[i] = data[j];
		data[j] = tmp;
		++i;
		--j;
	}
}

MyString::MyString(char c, int len) {
	length = capacity = len;
	data = new char[len];
	memset(data, c, length * sizeof(data[0]));
}