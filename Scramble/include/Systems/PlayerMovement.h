#pragma once
#include "Systems/DefaultSystem.h"
#include "Components/Vector2D.h"
#include "Components/Components.h"
#include "Components/Positionf.h"

class MovementHandler : bloom::systems::System {
public:
	using bloom::systems::System::DefaultSystem;

	void update(double deltaTime = 0.0) {
		int w = 800, h = 600;
		m_registry.group<>(entt::get<Vector2D, Positionf, bloom::components::Size>).each(
			[&](Vector2D& vector, Positionf& position, bloom::components::Size& size) {
				position.x += vector.x * (deltaTime / 1000.0);
				position.y += vector.y * (deltaTime / 1000.0);
				if (position.x < 0) position.x = 0.0;
				else if (position.x > 800 - size.w) position.x = 800 - size.w;
				if (position.y < 0) position.y = 0.0;
				else if (position.y > 600 - size.h) position.y = 600 - size.h;

				vector.x = 0, vector.y = 0;
			}
		);
	}
};
