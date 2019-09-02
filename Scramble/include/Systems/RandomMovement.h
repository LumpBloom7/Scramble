#pragma once
#include "Systems/DefaultSystem.h"
#include "Components/Vector2D.h"
#include "Components/EnemyComponent.h"


class RandomMovement : public bloom::systems::System {
public:
	using bloom::systems::System::DefaultSystem;

	void update(double deltaTime = 0.0) {
		srand(static_cast<uint32_t>(time(nullptr)));
		m_registry.group<>(entt::get<Vector2D, EnemyComponent>).each(
			[](auto& vector, auto& enemyComp) {
				int randX = (rand() % 10), randY = (rand() % 10);
				vector.x += randX;
				vector.y += randY;

				vector.x = (randX % 2 == 0 ? vector.x * -1 : vector.x);
				vector.y = (randY % 2 == 0 ? vector.y * -1 : vector.y);

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