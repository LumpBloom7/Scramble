#include "Systems/EnemyAI/Kamikaze.h"

namespace EnemyAI {
	void kamikaze(entt::registry& registry, entt::entity enemy, entt::entity player, double deltaTime) {
		auto playerDet = registry.get<Positionf, Size>(player);
		auto enemyDet = registry.get<Positionf, Size, Vector2D, Speed>(enemy);

		auto vector = Vector2D{
			(std::get<0>(playerDet).x + std::get<1>(playerDet).w / 2) - (std::get<0>(enemyDet).x + std::get<1>(enemyDet).w / 2),
			(std::get<0>(playerDet).y + std::get<1>(playerDet).h / 2) - (std::get<0>(enemyDet).y + std::get<1>(enemyDet).h / 2)
		};

		double length = std::sqrt((vector.x * vector.x) + (vector.y * vector.y));
		if (length != 0.0) {
			vector.x /= length;
			vector.y /= length;
		}

		std::get<2>(enemyDet) = vector;
	}
}