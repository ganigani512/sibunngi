#pragma once
#include "DxLib.h"
#include "../support/Support.h"
#include "../support/vec3.h"
#include <time.h>
#include <random>
#include <math.h>
#include <vector>
#include <list>
#include "../game/utility.h"




class Object {
public:

    t2k::vec3 maxsize = t2k::vec3(1000, 600, 0);//àÍî‘Ç≈Ç©Ç¢î†ÇÃècâ°ÇÃïù
	Object(t2k::vec3 Position, t2k::vec3 MaxSize) {
		pos = Position;
		size = MaxSize;
		hit = false;
		speed = t2k::vec3((rand()) % 3 + 1, (rand()) % 3 + 1, 0);
	}

	t2k::vec3 pos, size, speed;
	unsigned int color;
	bool hit;

	void move() {
		if (pos.x + (size.x / 2) >= maxsize.x) {
			speed.x = -(rand() % 3);
		}
		if (pos.x - (size.x / 2) <= 0) {
			speed.x = rand() % 3;
		}
		if (pos.y + (size.y / 2) >= maxsize.y) {
			speed.y = -(rand() % 3);
		}
		if (pos.y - (size.y) <= 0) {
			speed.y = rand() % 3;
		}



		pos += speed;

	};

	void render() {
		color = 0xffff0000;//ê¬
		if (hit == true) {
			color = 0xff00ff00;//ê‘
		}
		DrawBox(pos.x - size.x / 2, pos.y - size.x / 2, pos.x + size.x / 2, pos.y + size.y / 2, color, false);
		hit = false;
	};

};


class Room {
public:

	t2k::vec3 pos;
	t2k::vec3 size;
	int mortonNum;
	std::list<Object*> roomObjectList;

	void render() {
		unsigned int co = 0xff002000;
		if (roomObjectList.size()>0) {
			co = 0xff0000ff;
		}
		DrawBox(pos.x, pos.y, pos.x + size.x, pos.y + size.y, co, false);
		DrawStringEx(pos.x + (size.x / 2), pos.y + (size.y / 2), co, "%d", mortonNum);
	}
};

class Sibunngi {
private:
	Sibunngi() {
		hitcount = 0;
		syokika();
	}
	//	Sibunngi() { const Sibunngi& };

	Sibunngi& operator=(const Sibunngi&);

public:
	static  Sibunngi* getInstance() {
		static Sibunngi *inst;

		if (inst == nullptr) {
			inst = new Sibunngi();
		}
		return inst;
	}
	t2k::vec3 maxsize = t2k::vec3(1000, 600, 0);//àÍî‘Ç≈Ç©Ç¢î†ÇÃècâ°ÇÃïù

	int hitcount;
	const int levelmax = 3;//ï™äÑÉåÉxÉã
	static const int hakonokazu = 200;

	std::vector<int*> x;
	std::list<Object*> obj;
	Object *mouse;
	Object *hako[hakonokazu];
	std::vector<Room> room[3/*levelmax*/ + 1];
	std::list<Room*> InroomList;

	void set(int i, int v, int x, int y);
	int GetMortonNum(t2k::vec3 pos, t2k::vec3 size);
	int GetDivideLevel(int LeftUp, int RightDown);
	int warizan(int a);
	void syokika();
	void SibunngiCollision(int dividelevel, int mortonnum);

};