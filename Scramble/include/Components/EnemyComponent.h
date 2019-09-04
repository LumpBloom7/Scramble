#pragma once

struct EnemyComponent {
	enum class EnemyType {
		solid,
		kamikaze
	} type;

	double health = 100;

	int aggressiveness = 0;

	double maxSpeed = 0;
	double acceleration = 0;
	double decceleration = 0;

};