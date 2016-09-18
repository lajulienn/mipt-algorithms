#pragma once
#include <string>

class GameObject {
private:
	int x_;
	int y_;
public:
	GameObject(int, int);
   ~GameObject();
	int getx() const { return x_; }
	int gety() const { return y_; }
	 void print() const;
	void move_to(int, int);
};

class Creature : public GameObject {
private:
	int hit_points_;
public:
	Creature(int, int, int);
    ~Creature();
    virtual void print() const;
	int gethp() const { return hit_points_; }
};

class Mob : public Creature {
private: 
	int lane_;
public:
	Mob(int, int, int, int);
	~Mob();
	int getlane() const { return lane_; }
	void print() const;
};

class Hero : public Creature {
private:
	std::string name_;
public:
	Hero(std::string, int, int, int);
	~Hero();
	std::string getname() const { return name_; }
	void print() const;
};

void print_objects(GameObject *objects[], int size);
void destroy_objects(GameObject *objects[], int size);