#pragma once
#include <bitset>

struct PlayerComponent {
	// Counters
	int score;
	int kills;
	int graze;

	// Equipment
	int lives;
	int bombs;
	int continues;

	// Focus mode
	bool focused = false;

	double speed = 300.0;
	std::bitset<10> perks;
};