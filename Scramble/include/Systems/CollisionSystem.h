#pragma once
#include "Systems/DefaultSystem.h"
#include "Components/Hitbox.h"
#include "Components/Size.h"
#include "Components/Position.h"
#include "Components/PlayerComponent.h"
#include "Components/EnemyComponent.h"

class CollisionSystem : public bloom::systems::System {
public:
	using bloom::systems::System::DefaultSystem;	
	using Position = bloom::components::Position;
	using Size = bloom::components::Size;

	void update(double deltaTime = 0.0) {
		timeDifference += deltaTime;
		m_registry.group<>(entt::get<Hitbox, Size, Position>).each(
			[&](auto& entity, Hitbox& hitbox, Size& size, Position& position) {
				int xOffset = (size.w - hitbox.w) / 2, yOffset = (size.h - hitbox.h) / 2;
				m_registry.group<>(entt::get<Hitbox, Size, Position>).each(
					[&](auto& entity2, Hitbox& hitbox2, Size& size2, Position& position2) {
						int xOffset2 = (size2.w - hitbox2.w) / 2, yOffset2 = (size2.h - hitbox2.h) / 2;
						if (entity != entity2) {
							if (position.x + xOffset < position2.x + xOffset2 + hitbox2.w &&
								position.x + xOffset + hitbox.w > position2.x + xOffset2 &&
								position.y + yOffset < position2.y + yOffset2 + hitbox2.h &&
								position.y + yOffset + hitbox.h > position2.y + yOffset2) {
								std::cout << "[" << hitbox.name << "] collided with [" << hitbox2.name << "]." << std::endl;
							}
						}
					}
				);
			}
		);
	}

private:
	double timeDifference = 0.0;
};