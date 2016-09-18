#include "MyObjects.h"
#include <iostream>

GameObject::GameObject(int x, int y) {
	x_ = x;
	y_ = y;
	std::cout << "Creating GameObject at  (" << x_ << "," << y_ << ")" << std::endl;
}

GameObject::~GameObject() {
	std::cout << "Deleting GameObject at  (" << x_ << "," << y_ << ")" << std::endl;
	int aa = 0;
}

void GameObject::print() const {
	std::cout << "This is GameObject at  (" << x_ << "," << y_ << ")" << std::endl;
}

void GameObject::move_to(int nx, int ny) {
	x_ = nx;
	y_ = ny;
}

Creature::Creature(int hp, int x, int y) : GameObject(x, y) {
	hit_points_ = hp;
	std::cout << "Creating Creature at  (" << getx() << "," << gety() << ") with hp = " << hp << std::endl;
}

Creature::~Creature() {
	std::cout << "Deleting Creature at  (" << getx() << "," << gety() << ") with hp = " << gethp() << std::endl;
}

Mob::Mob(int lane, int hp, int x, int y) : Creature(hp, x, y){
	lane_ = lane;
	std::cout << "Creating Mob at  (" << getx() << "," << gety() << ") with hp = " << hp << " on lane "<< lane << std::endl;
}
Mob::~Mob() {
	std::cout << "Creating Mob at  (" << getx() << "," << gety() << ") with hp = " << gethp() << " on lane " << getlane() << std::endl;
}

void Creature::print() const {
	std::cout << "This is Creature at (" << getx() << "," << gety() << ") with hp = "<< gethp() << std::endl;
}

void print_objects(GameObject *objects[], int size) {
	for (int i = 0; i < size; ++i)
		objects[i]->print();
}

void destroy_objects(GameObject *objects[], int size) {
	for (int i = 0; i < size; ++i)
		delete objects[i];
}

Hero::Hero(std::string name, int hp, int x, int y) :Creature(hp, x, y) {
	name_ = name;
	std::cout << "Creating Hero at (" << getx() << "," << gety() << ") with hp = " << gethp() << " on lane " << getname() << std::endl;
}

Hero::~Hero() {
	std::cout << "Deleting Hero at (" << getx() << "," << gety() << ") with hp = " << gethp() << " with name " << getname() << std::endl;
}

void Mob::print() const {
	std::cout << "This is Mob at  (" << getx() << "," << gety() << ") with hp = " << gethp() << " on lane " << getlane() << std::endl;
}

void Hero::print() const {
	std::cout << "This is Hero at (" << getx() << "," << gety() << ") with hp = " << gethp() << " with name " << getname() << std::endl;
}