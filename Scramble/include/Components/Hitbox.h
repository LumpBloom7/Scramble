#pragma once
#include <deque>
struct Grid {
	int x = 0, y = 0;
};
struct Hitbox {
	enum class Type {
		friendly,
		enemy,
		friendlyBullet,
		enemyBullet
	} type;
	
	std::string name = "Object";
	double w, h;
	double xOffset, yOffset;

	std::vector<Grid> intersectedGrids;
};