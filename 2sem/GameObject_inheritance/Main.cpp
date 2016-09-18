#include "MyObjects.h"
#include <iostream>

int main() {
	GameObject *objects[] = { new Mob(1, 50, 70, 80) , new Hero("Alise", 20, 100, 100)};
	print_objects(objects, 2);
	destroy_objects(objects, 2);
	//Mob *m = (Mob *) objects[0];
	//delete m;
	return 0;
}