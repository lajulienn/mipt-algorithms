#define _CRTDBG_MAP_ALLLOC

#include <crtdbg.h>

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "heroes_of_dungeons.h"

using namespace std;

class AutoLeakChecker
{
public:
	~AutoLeakChecker() {
		_CrtDumpMemoryLeaks();
	}
} global_leak_checker;

int main() {
	std::ofstream log("commands.log");
	World *my_world = nullptr;
	string trash;
	for (;;) {
		cout << "> ";

		string line;
		getline(cin, line);

		log << line << std::endl;

		istringstream command(line);

		std::string instruction;
		command >> instruction;
		if (instruction == "map") {
			int x = 0;
			int y = 0;
			command >> x >> y;
			if (x <= 0 || y <= 0) {
				cout << "Wrong map size.\n";
				continue;
			}
			delete my_world;
			my_world = new World(x, y);
		} else if (instruction == "show") {
			if (!my_world) {
				cout << "No available map.\n";
				continue;
			}
			my_world->show();
			cout << endl;
		} else if (instruction == "create") {
			if (!my_world) {
				cout << "No available map.\n";
				continue;
			}
			string object;
			command >> object;
			if (object == "lake") {
				int depth = 0, x = 0, y = 0, size = 0;
				command >> trash >> depth >> trash >> x >> y >> trash >> size;

				if (depth < 0 || x < 0 || y < 0 || size < 0) {
					cout << "Wrong input.\n";
					continue;
				}

				my_world->add_object(new Lake(depth, x, y, size));
			} else if (object == "mountain") {
				int height = 0, x = 0, y = 0, size = 0;
				command >> trash >> height >> trash >> x >> y >> trash >> size;

				if (height < 0 || x < 0 || y < 0 || size < 0) {
					cout << "Wrong input.\n";
					continue;
				}

				my_world->add_object(new Mountain(height, x, y, size));
			} else if (object == "forest") {
				int x = 0, y = 0, size = 0;
				command >> trash >> x >> y >> trash >> size;

				if (x < 0 || y < 0 || size < 0) {
					cout << "Wrong input.\n";
					continue;
				}
				my_world->add_object(new Forest(x, y, size));
			} else if (object == "hero") {
				string name;
				int x = 0, y = 0, hp = 0;
				command >> name >> trash >> x >> y >> trash >> hp;

				if (x < 0 || y < 0 || hp < 0) {
					cout << "Wrong input.\n";
					continue;
				}

				my_world->add_object(new Hero(name, x, y, hp));
			} else if (object == "monster") {
				int x = 0, y = 0, hp = 0;
				command >> trash >> x >> y >> trash >> hp;

				if (x < 0 || y < 0 || hp < 0) {
					cout << "Wrong input.\n";
					continue;
				}

				my_world->add_object(new Monster(x, y, hp));
			} else {
				command.ignore(1000, '\n');
				continue;
			}
		} else if (instruction == "dump") {
			if (!my_world) {
				cout << "No available map.\n";
				continue;
			}
			my_world->dump();
		} else if (instruction == "move") {
			if (!my_world) {
				cout << "No available map.\n";
				continue;
			}
			int index, x, y;
			command >> index >> x >> y;
			if (index < 1 || index > my_world->get_count()) {
				cout << "Wrong index.\n";
				continue;
			}
			my_world->move_object(index, x, y);
		} else if (instruction == "help") {
			cout << "1) map <width> <height> - create new map.\n";
			cout << "2) show - draw current map condition.\n";
			cout << "3) create + \n"
				<< "	lake depth <depth> at <x> <y> size <size>\n"
				<< "	mountain height <height> at <x> <y> size <size>\n"
				<< "	forest at <x> <y> size <size>\n"
				<< "	hero <name> at <x> <y> hp <hp>\n"
				<< "	monster at <x> <y> hp <hp>\n";
			cout << "4) dump - show descriptions of all objects on the current map.\n";
			cout << "5) quit - close map editor.\n";
		} else if (instruction == "quit") {
			delete my_world;
			return 0;
		} else {
			cout << "Unknown command." << endl;
		}
	}
	return 0;
}

