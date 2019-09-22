#include "Systems/EnemyAI/Kamikaze.h"

namespace EnemyAI {
	void kamikaze(entt::registry& registry, entt::entity enemy, entt::entity player, double deltaTime) {
		auto playerDet = registry.get<Positionf, Size>(player);
		auto enemyDet = registry.get<Positionf, Size, Vector2D, Speed>(enemy);
	}
}