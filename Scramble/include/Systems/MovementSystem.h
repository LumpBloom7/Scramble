#pragma once
#include "Systems/DefaultSystem.h"
#include "Components/Vector2D.h"
#include "Components/Components.h"
#include "Components/Positionf.h"
#include "Components/Speed.h"
#include "Components/PlayerControl.h"
#include "Components/Enemy.h"
#include "Components/Destroyed.h"

class MovementSystem : bloom::systems::System {
public:
	using bloom::systems::System::DefaultSystem;

	void update(double deltaTime = 0.0) {
		deltaTime /= 1000.0;
		m_registry.group<>(entt::get<Vector2D, Positionf, Speed, bloom::components::Size>, entt::exclude<Destroyed>).each(
			[&](auto& entity, Vector2D& vector, Positionf& position, Speed& speed, bloom::components::Size& size) {
				//if (!m_registry.has<Enemy>(entity)) {
					position.x += vector.x * std::abs(speed.xValue) * deltaTime;
					position.y += vector.y * std::abs(speed.yValue) * deltaTime;

					if (m_registry.has<PlayerControl>(entity)) {
						auto& size = m_registry.get<bloom::components::Size>(entity);
						if (position.x < 0) position.x = 0.0;
						else if (position.x > static_cast<double>(800) - size.w) position.x = static_cast<double>(800) - size.w;
						if (position.y < 0) position.y = 0.0;
						else if (position.y > static_cast<double>(600) - size.h) position.y = static_cast<double>(600) - size.h;
					}
					else if (m_registry.has<Enemy>(entity)) {
						std::exception("");
					}
				//}
			}
		);
	}
};
