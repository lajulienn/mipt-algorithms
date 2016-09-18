#pragma once

class Stack {
public:
	Stack(int init_size = 100);
	Stack(const Stack &src);
	~Stack();
	void push(int x);
	int pop();
	int get_size();
	int top();
	void clear();
private:
	int *data;
	int count;
	int capacity;
};