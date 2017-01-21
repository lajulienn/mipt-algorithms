#ifndef MYSTRING_H_
#define MYSTRING_H_
#include <ostream>

class MyString {
public:
	MyString(const MyString&);
	MyString(char);
	MyString(const char * = "");
	MyString(char c, int len);
	MyString(int len);
	~MyString();
	MyString& operator=(char);
	MyString& operator=(const char *);
	MyString& operator=(const MyString&);
	MyString operator+(const MyString&) const; 
	MyString operator+(char) const; 
	MyString operator+(const char *) const;
	MyString& MyString::operator+=(const MyString&);
	MyString& MyString::operator+=(char);
	MyString& MyString::operator+=(const char *);
	char operator[](int) const;
	char& operator[](int);
	friend std::ostream& operator<<(std::ostream&, const MyString&);
	friend std::istream& operator>>(std::istream&, MyString&);
	friend MyString operator+(char, const MyString&); 
	friend MyString operator+(const char *, const MyString&); 
	int get_length() const; 
	void reverse();
private:
	int capacity;
	int length;
	char *data;
	void capacity_check(int);
};

std::ostream& operator<<(std::ostream&, const MyString&);
std::istream& operator>>(std::istream&, MyString&); 
MyString operator+(char, const MyString&);
MyString operator+(const char *, const MyString&);

#endif