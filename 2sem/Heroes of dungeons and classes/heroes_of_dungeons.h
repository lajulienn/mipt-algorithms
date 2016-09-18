#ifndef HEROES_OF_DUNGEONS_H_
#define HEROES_OF_DUNGEONS_H_

#include <vector>

const int default_creature_size = 1;

class GameObject {
public:
	GameObject(int x, int y, int size);
	virtual ~GameObject() {}

	int get_x() const { return x_; }
	int get_y() const { return y_; }
	int get_size() const { return size_; }

	void move_to(int new_x, int new_y);
	virtual void print() const {}
	virtual char symbol() const { return '?'; }
private:
	int x_, y_;
	int size_;
};

class Creature : public GameObject {
public:
	Creature(int x, int y, int hp);
	virtual ~Creature() {}

	virtual void print() const {}
	virtual char symbol() const { return '?'; }
	int get_hp() const { return hp_; }
private:
	int hp_;
};

class Monster : public Creature {
public:
	Monster(int x, int y, int hp) : Creature(x, y, hp) {}
	virtual ~Monster() {}

	virtual void print() const;
	virtual char symbol() const { return 'm'; }
};

class Hero : public Creature {
public:
	Hero(std::string name, int x, int y, int hp) : Creature(x, y, hp) { name_ = name; }
	virtual ~Hero() {}

	std::string get_name() const { return name_; }

	virtual void print() const;
	virtual char symbol() const { return name_[0]; }
private:
	std::string name_;
};

class Terrain : public GameObject {
public:
	Terrain(int x, int y, int size) : GameObject(x, y, size) {}
	virtual ~Terrain() {}

	virtual void print() const {}
	virtual char symbol() const { return '?'; }
};

class Lake : public Terrain {
public:
	Lake(int depth, int x, int y, int size) : Terrain(x, y, size) { depth_ = depth; }
	virtual ~Lake() {}

	int get_depth() const { return depth_; }

	virtual void print() const;
	virtual char symbol() const { return 'o'; }
private:
	int depth_;
};

class Mountain :public Terrain {
public:
	Mountain(int height, int x, int y, int size) : Terrain(x, y, size) { height_ = height; }
	virtual ~Mountain() {}

	int get_height() const { return height_; }

	virtual void print() const;
	virtual char symbol() const { return '^'; }
private:
	int height_;
};

class Forest : public Terrain {
public:
	Forest(int x, int y, int size) : Terrain(x, y, size) {}
	virtual ~Forest() {}

	virtual void print() const;
	virtual char symbol() const { return 'F'; }
};

class World {
public:
	World(int width, int height);
	World(const World&) = delete;
	void operator=(const World&) = delete;
	~World();

	void show() const { std::cout << map; }
	void add_object(GameObject *new_object);
	void dump() const;
	int get_count() { return objects.size(); }
	void move_object(int index, int x, int y);
private:
	void render();
	GameObject& get_object_by_index(int index) const;

	std::vector<GameObject *> objects;
	char *map;
	int width_, height_;
};

#endif