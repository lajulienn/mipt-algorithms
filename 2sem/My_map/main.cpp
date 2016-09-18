#define _CRTDBG_MAP_ALLLOC

#include <crtdbg.h>

#include <iostream>
#include <string>
#include "my_map.h"

using namespace std;

typedef MyMap<string, int> LikeMap;

void add(string name, LikeMap &vk);
void erase(string name, LikeMap &vk);
void clear(LikeMap &vk);
void like(string name, LikeMap &vk);
void dislike(string name, LikeMap &vk);
void show(string name, LikeMap &vk);
void dump(LikeMap &vk);

class AutoLeakChecker
{
public:
	~AutoLeakChecker() {
		_CrtDumpMemoryLeaks();
	}
} global_leak_checker;

int main() {
	LikeMap vk;

	string command = "";
	string name = "";
	while (command != "exit") {
		std::cout << ">>";
		cin >> command;
		std::cout << '[' << command << ']' << std::endl;
		if (command == "dump") {
			dump(vk);
		} else if (command == "add") {
			cin >> name;
			add(name, vk);
		} else if (command == "delete") {
			cin >> name;
			erase(name, vk);
		} else if (command == "clear") {
			clear(vk);
		} else if (command == "like") {
			cin >> name;
			like(name, vk);
		} else if (command == "dislike") {
			cin >> name;
			dislike(name, vk);
		} else if (command == "show") {
			cin >> name;
			show(name, vk);
		} else if (command == "empty") {
			if (vk.empty())
				cout << "Yes\n";
			else
				cout << "No\n";
		} else if (command == "size") {
			cout << vk.size() << endl;
		} else if (command == "help") {
			cout <<
				"add <name>\n" <<
				"delete <name>\n" <<
				"like <name>\n" <<
				"dislike <name>\n" <<
				"show <name>\n" <<
				"clear\n" <<
				"empty\n" <<
				"size\n" <<
				"dump\n" <<
				"exit\n";
		}
	}
	clear(vk);
	cout << "Bye!" << endl;

	return 0;
}

void add(string name, LikeMap& vk) {
	if (vk.exist(name) == 1) {
		cout << "This name already exists." << endl;
		return;
	}
	vk[name] = 0;
}

void erase(string name, LikeMap& vk) {
	if (vk.exist(name) == 0) {
		cout << "No such name." << endl;
		return;
	}
	vk.erase(name);
}
void clear(LikeMap &vk) {
	vk.clear();
}

void like(string name, LikeMap& vk) {
	if (vk.exist(name) == 0) {
		cout << "No such name." << endl;
		return;
	}
	++vk[name];
}

void dislike(string name, LikeMap& vk) {
	if (vk.exist(name) == 0) {
		cout << "No such name." << endl;
		return;
	}
	--vk[name];
}

void show(string name, LikeMap& vk) {
	if (vk.exist(name) == 0) {
		cout << "No such name." << endl;
		return;
	}
	cout << vk[name] << endl;
}

void dump(LikeMap& vk) {
	//for (auto node : vk)
	//	cout << node.first << " " << node.second << endl;
	vk.dump();
}
