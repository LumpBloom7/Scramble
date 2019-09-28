#pragma once
#include "Components/Vector2D.h"
#include "Components/Enemy.h"
#include "Components/PlayerControl.h"
#include "Systems/EnemyAI/Kamikaze.h"
#include "Components/Destroyed.h"

namespace systems {
	static void enemyBehaviorSystem(entt::registry& registry, double deltaTime = 0.0) {
		entt::entity player = *registry.view<PlayerControl>().begin();
		registry.view<Enemy>().each(
			[&](auto& entity, Enemy& enemyComp) {
				if (!registry.has<Destroyed>(entity)) {
					if (enemyComp.type == Enemy::EnemyType::kamikaze) {
						EnemyAI::kamikaze(registry, entity, player, deltaTime);
					}
				}
			}
		);
	}
}