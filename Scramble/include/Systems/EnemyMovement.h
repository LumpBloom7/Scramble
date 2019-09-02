#pragma once
#include "Systems/DefaultSystem.h"
#include "Components/Vector2D.h"
#include "Components/EnemyComponent.h"
#include "Components/PlayerComponent.h"


class EnemyMovement : public bloom::systems::System {
public:
	using bloom::systems::System::DefaultSystem;

	void update(double deltaTime = 0.0) {
		srand(static_cast<uint32_t>(time(nullptr)));
		auto players = m_registry.group<>(entt::get<Positionf, PlayerComponent>);
		m_registry.group<>(entt::get<Vector2D, EnemyComponent, Positionf>).each(
			[&](auto& vector, auto& enemyComp, auto& positionf) {

				vector.x += players.get<Positionf>(players[0]).x - positionf.x;
				vector.y += players.get<Positionf>(players[0]).y - positionf.y;

				double length = std::sqrt((vector.x * vector.x) + (vector.y * vector.y));
				if (length != 0.0) {
					vector.x /= length;
					vector.y /= length;
				}
				vector.x *= enemyComp.speed;
				vector.y *= enemyComp.speed;
			}
		);
	}
};