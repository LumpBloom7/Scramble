#pragma once

struct Grid {
	int x = -1, y = -1;
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

	std::vector<Grid> intersectedGrids{};
};