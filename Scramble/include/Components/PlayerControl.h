#pragma once
#include <bitset>

struct PlayerControl {
	// Counters
	int score = 0;
	int kills = 0;
	int graze = 0;

	// Equipment
	int lives = 3;
	int bombs = 2;
	int continues = 5;

	// Focus mode
	bool focused = false;
	bool wasFocused = false;

	int hDirection = 1;

	std::bitset<10> perks;
};