#include <iostream>
#include <string>
#include <map>

using namespace std;

typedef map <string, int> LikeMap;

void add(string name, LikeMap& vk);
void erase(string name, LikeMap& vk);
void like(string name, LikeMap& vk);
void dislike(string name, LikeMap& vk);
void show(string name, LikeMap& vk);
void dump(LikeMap& vk);

int main() {
	LikeMap vk;

	string command = "";
	string name = "";
	while (command != "exit") {
		cout << ">>";
		cin >> command;
		cout << command;
		if (command == "dump")
			dump(vk);
		else if (command == "add") {
			cin >> name;
			cout << " " << name << endl;
			add(name, vk);
		}
		else if (command == "delete") {
			cin >> name;
			cout << " " << name << endl;
			erase(name, vk);
		}
		else if (command == "clear") {
			vk.clear();
		}
		else if (command == "like") {
			cin >> name;
			cout << " " << name << endl;
			like(name, vk);
		}
		else if (command == "dislike") {
			cin >> name;
			cout << " " << name << endl;
			dislike(name, vk);
		}
		else if (command == "show") {
			cin >> name;
			cout << " " << name << endl;
			show(name, vk);
		}
	}

	cout << "Bye!" << endl;
	return 0;
}

void add(string name, LikeMap& vk) {
	if (vk.count(name) == 1) {
		cout << "This name already exists." << endl;
		return;
	}
	vk[name] = 0;
}

void erase(string name, LikeMap& vk) {
	if (vk.count(name) == 0) {
		cout << "No such name." << endl;
		return;
	}
	vk.erase(name);
}

void like(string name, LikeMap& vk) {
	if (vk.count(name) == 0) {
		cout << "No such name." << endl;
		return;
	}
	++vk[name];
}

void dislike(string name, LikeMap& vk) {
	if (vk.count(name) == 0) {
		cout << "No such name." << endl;
		return;
	}
	--vk[name];
}

void show(string name, LikeMap& vk) {
	if (vk.count(name) == 0) {
		cout << "No such name." << endl;
		return;
	}
	cout << vk[name] << endl;
}

void dump(LikeMap& vk) {
	for (LikeMap::const_iterator it = vk.begin(); it != vk.end(); ++it)
		cout << it->first << " " << it->second << endl;
}
