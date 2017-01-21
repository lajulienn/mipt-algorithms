#include <iostream>
#include <string>

#include "heroes_of_dungeons.h"

GameObject::GameObject(int x, int y, int size) {
	x_ = x;
	y_ = y;
	size_ = size;
}

void GameObject::move_to(int new_x, int new_y) {
	x_ = new_x;
	y_ = new_y;
}

Creature::Creature(int x, int y, int hp) : GameObject(x, y, default_creature_size){
	hp_ = hp;
}

void Monster::print() const {
	std::cout << "Some monster with hp = " << get_hp() <<
		" at (" << get_x() << "," << get_y() << ")" << std::endl;
}

void Hero::print() const {
	std::cout << "Great hero " << get_name() << " with hp = " << get_hp() <<
		" at (" << get_x() << "," << get_y() << ")" << std::endl;
}

void Lake::print() const {
	std::cout << "Clean lake of depth = " << get_depth() <<
		" at (" << get_x() << "," << get_y() << ") size = " << get_size() << std::endl;
}

void Mountain::print() const {
	std::cout << "Big mountain " << get_height() <<
		" feet height at (" << get_x() << "," << get_y() << ") size = " << get_size() << std::endl;
}

void Forest::print() const {
	std::cout << "Forest at (" << get_x() << "," << get_y() << ") size = " << get_size() << std::endl;
}

World::World(int width, int height) {
	width_ = width;
	height_ = height;
	map = new char[height*(width * 2 + 1) + 1];
	for (int i = 0; i < height; ++i) {
		map[i*(width * 2 + 1) + width * 2] = '\n';
	}
	map[height*(width * 2 + 1)] = '\0';
	for (int oy = 0; oy < height; ++oy) {
		for (int ox = 0; ox < width * 2; ox += 2) {
			map[(width * 2 + 1) * oy + ox] = '.';
		}
	}
	for (int oy = 0; oy < height; ++oy) {
		for (int ox = 1; ox < width * 2; ox += 2) {
			map[(width * 2 + 1) * oy + ox] = ' ';
		}
	}
}

World::~World() {
	int count = objects.size();
	for (int i = 0; i < count; ++i) {
		delete objects[i];
	}
	delete[] map;
}

void World::add_object(GameObject *new_object) {
	if (new_object->get_x() + new_object->get_size() > width_ || new_object->get_y() + new_object->get_size() > height_) {
		std::cout << "Your object is beyond current map.\n";
		delete new_object;
		return;
	}
	objects.push_back(new_object);
	render();
}

void World::render() {
	for (int oy = 0; oy < height_; ++oy) {
		for (int ox = 0; ox < width_ * 2; ox += 2) {
			map[(width_ * 2 + 1) * oy + ox] = '.';
		}
	}
	int count = get_count();
	for (int i = 0; i < count; ++i) {
		GameObject *foo = objects.at(i);
		int size = foo->get_size();
		int x = foo->get_x();
		int y = foo->get_y();
		for (int ox = 0; ox < size; ++ox) {
			for (int oy = 0; oy < size; ++oy) {
				int index = (y + oy) * (width_ * 2 + 1) + (x + ox) * 2 ;
				map[index] = foo->symbol();
			}
		}
	}
}

void World::dump() const {
	int count = objects.size();
	for (int i = 0; i < count; ++i) {
		std::cout << i + 1 << ". ";
		objects[i]->print();
	}
}

GameObject& World::get_object_by_index(int index) const {
	return *objects[index - 1];
}

void World::move_object(int index, int x, int y) {
	get_object_by_index(index).move_to(x, y);
	render();
}
