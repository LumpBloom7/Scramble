#pragma once

struct Hitbox {
	enum class Type {
		friendly,
		enemy,
		friendlyBullet,
		enemyBullet
	} type;
	double w, h;
	double xOffset, yOffset;
};