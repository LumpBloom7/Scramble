#pragma once

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
};