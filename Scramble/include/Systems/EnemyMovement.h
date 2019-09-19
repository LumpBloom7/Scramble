#pragma once
#include "Systems/DefaultSystem.h"
#include "Components/Vector2D.h"
#include "Components/EnemyComponent.h"
#include "Components/PlayerComponent.h"


class EnemyMovement : public bloom::systems::System {
public:
	using bloom::systems::System::DefaultSystem;

	void update(double deltaTime = 0.0) {
		entt::entity players = *m_registry.view<Positionf, PlayerComponent, bloom::components::Size>().begin();
		m_registry.view<Vector2D, EnemyComponent, Positionf, bloom::components::Size>().each(
			[&](auto& vector, auto& enemyComp, auto& positionf, auto& size) {
				if (enemyComp.type == EnemyComponent::EnemyType::kamikaze) {
					double xThrust = m_registry.get<Positionf>(players).x + m_registry.get<bloom::components::Size>(players).w / 2 - (positionf.x + size.w / 2);
					double yThrust = m_registry.get<Positionf>(players).y + m_registry.get<bloom::components::Size>(players).h / 2 - (positionf.y + size.h / 2);

					double length = std::sqrt((xThrust * xThrust) + (yThrust * yThrust));
					if (length != 0.0) {
						xThrust /= length;
						yThrust /= length;
					}

					if (xThrust != 0.0) {
						if ((vector.x < 0.0 && xThrust > 0.0) || (vector.x > 0.0 && xThrust < 0.0))
							vector.x += xThrust * (enemyComp.acceleration * (deltaTime / 1000)) * 5;
						else
							vector.x += xThrust * (enemyComp.acceleration * (deltaTime / 1000));
						if (vector.x > enemyComp.maxSpeed)
							vector.x = enemyComp.maxSpeed;
						else if (vector.x < -enemyComp.maxSpeed)
							vector.x = -enemyComp.maxSpeed;
					}
					else {
						if (vector.x > 0) {
							vector.x -= enemyComp.decceleration * (deltaTime / 1000);
							if (vector.x < 0.0) {
								vector.x = 0.0;
							}
						}
						else if (vector.x < 0) {
							vector.x += enemyComp.decceleration * (deltaTime / 1000);
							if (vector.x > 0.0) {
								vector.x = 0.0;
							}
						}
					}

					if (yThrust != 0.0) {
						if ((vector.y < 0.0 && yThrust > 0.0) || (vector.y > 0.0 && yThrust < 0.0))
							vector.y += yThrust * (enemyComp.acceleration * (deltaTime / 1000)) * 5;
						else
							vector.y += yThrust * (enemyComp.acceleration * (deltaTime / 1000));

						if (vector.y > enemyComp.maxSpeed)
							vector.y = enemyComp.maxSpeed;
						else if (vector.y < -enemyComp.maxSpeed)
							vector.y = -enemyComp.maxSpeed;
					}
					else {
						if (vector.y > 0) {
							vector.y -= enemyComp.decceleration * (deltaTime / 1000);
							if (vector.y < 0.0) {
								vector.y = 0.0;
							}
						}
						else if (vector.y < 0) {
							vector.y += enemyComp.decceleration * (deltaTime / 1000);
							if (vector.y > 0.0) {
								vector.y = 0.0;
							}
						}
					}
					positionf.x += vector.x * (deltaTime / 1000);
					positionf.y += vector.y * (deltaTime / 1000);
				}
			}
		);
	}
};