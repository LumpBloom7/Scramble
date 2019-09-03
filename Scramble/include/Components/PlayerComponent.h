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
	bool wasFocused = false;

	double speed = 600.0;
	double playerVelocity;
	std::bitset<10> perks;
};