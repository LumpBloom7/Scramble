#pragma once
#include "Systems/DefaultSystem.h"
#include "Components/Vector2D.h"
#include "Components/Components.h"

class MovementHandler : bloom::systems::System {
public:
	using bloom::systems::System::DefaultSystem;

	void update(double deltaTime = 0.0) {
		int w = 800, h = 600;
		m_registry.group<>(entt::get<Vector2D, bloom::components::Position, bloom::components::Size>).each(
			[&](Vector2D& vector, bloom::components::Position& position, bloom::components::Size& size) {
				if (std::abs(vector.x) == std::abs(vector.y) && vector.x != 0) {
					if (vector.x > 0)
						position.x += 7;
					else if (vector.x < 0)
						position.x -= 7;

					if (vector.y > 0)
						position.y += 7;
					else if (vector.y < 0)
						position.y -= 7;
				}
				else {
					if (vector.x > 0)
						position.x += 10;
					else if (vector.x < 0)
						position.x -= 10;

					if (vector.y > 0)
						position.y += 10;
					else if (vector.y < 0)
						position.y -= 10;
				}

				if (position.x < 0) position.x = 0;
				else if (position.x > w - size.w) position.x = w - size.w;

				if (position.y < 0) position.y = 0;
				else if (position.y > h - size.h) position.y = h - size.h;

				vector.x = 0, vector.y = 0;
			}
		);
	}
};
