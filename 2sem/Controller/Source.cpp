#include <iostream>
#include <string>
#include <memory>

using namespace std;

class Controller {
public:
	Controller(string name) : _name(name) { cout << name << endl; }
	~Controller() { cout << "~" << _name << endl; }

	string _name;
	weak_ptr<Controller> other_controller;
};

int main() {
	shared_ptr<Controller> a(new Controller("a"));
	shared_ptr<Controller> b(new Controller("b"));
	a->other_controller = b;
	b->other_controller = a;

	return 0;
}