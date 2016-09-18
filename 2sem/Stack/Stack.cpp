#include "Stack.h"
#include <iostream>
#include <cstdlib>
#include <stdexcept>

const int INIT_SIZE = 2;

Stack::Stack(int init_size) {
	std::cout << "Constructor" << std::endl;
	data = new int[init_size];
	if (data == NULL)
		throw std::runtime_error("Stack::Stack: Memory wasn't allocated");
	count = 0;
	capacity = init_size;
}

Stack::Stack(const Stack &src) {
	std::cout << "Copy constructor" << std::endl;
	int init_size = src.capacity;
	data = new int[init_size];
	if (data == NULL)
		throw std::runtime_error("Stack::Stack(Stack *src): Memory wasn't allocated");
	for (int i = 0; i < init_size; ++i) {
		data[i] = src.data[i];
	}
	count = src.count;
	capacity = init_size;
}

Stack::~Stack() {
	std::cout << "Destructor" << std::endl;
	delete[] data;
}

void Stack::push(int x) {
	if (count >= capacity) {
		throw std::runtime_error("Stack::push: No memory");
	}
	data[count] = x;
	++count;
}

int Stack::pop() {
	if (count <= 0) {
		throw std::runtime_error("Stack::pop: Stack empty");
	}
	--count;
	return data[count];
}

int Stack::get_size() {
	return count;
}

void Stack::clear() {
	count = 0;
}

int Stack::top() {
	if (count > 0)
		return data[0];
	else
		throw std::runtime_error("Stack::top: Stack empty");
}