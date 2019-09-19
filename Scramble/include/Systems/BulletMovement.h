#pragma once
#include "Systems/DefaultSystem.h"
#include "Components/Vector2D.h"
#include "Components/Components.h"
#include "Components/Positionf.h"
#include "Components/BulletComponent.h"

class BulletMovement : bloom::systems::System {
public:
	using bloom::systems::System::DefaultSystem;

	void update(double deltaTime = 0.0) {
		m_registry.view<Vector2D, Positionf, BulletComponent>().each(
			[deltaTime](Vector2D& vector, Positionf& position, BulletComponent& bullet) {
				position.x += vector.x * bullet.speed * (deltaTime / 1000.0);
				position.y += vector.y * bullet.speed * (deltaTime / 1000.0);
			}
		);
	}
};
