#pragma once

struct Enemy{
	enum class EnemyType {
		solid,
		kamikaze
	} type;
	int aggressiveness = 0;
};