#pragma once
#include "Systems/DefaultSystem.h"
#include "Components/Vector2D.h"
#include "Components/Enemy.h"
#include "Components/PlayerControl.h"
#include "Systems/EnemyAI/Kamikaze.h"
#include "Components/Destroyed.h"


class EnemyBehavior : public bloom::systems::System {
public:
	using bloom::systems::System::DefaultSystem;

	void update(double deltaTime = 0.0) {
		entt::entity player = *m_registry.view<PlayerControl>().begin();
		m_registry.view<Enemy>().each(
			[&](auto& entity, Enemy& enemyComp) {
				if (!m_registry.has<Destroyed>(entity)) {
					if (enemyComp.type == Enemy::EnemyType::kamikaze) {
						EnemyAI::kamikaze(m_registry, entity, player, deltaTime);
					}
				}
			}
		);
	}
};