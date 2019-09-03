#pragma once

struct EnemyComponent {
	double health;

	int aggressiveness;

	double maxSpeed = 500.0;
	double velocity = 0.0;
	double acceleration = 500.0;
	double decceleration = 60.0;

};