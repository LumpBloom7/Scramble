#pragma once
#include "Systems/DefaultSystem.h"
#include "Components/Hitbox.h"
#include "Components/Size.h"
#include "Components/Position.h"
#include "Components/PlayerComponent.h"
#include "Components/EnemyComponent.h"

struct Points {
	Positionf start, end;
};

class CollisionSystem : public bloom::systems::System {
public:
	using bloom::systems::System::DefaultSystem;
	using Position = bloom::components::Position;
	using Size = bloom::components::Size;

	void update(double deltaTime = 0.0) {
		timeDifference += deltaTime;
		m_registry.group<>(entt::get<Hitbox, Size, Positionf, Vector2D>).each(
			[&](auto& entity, Hitbox& hitbox, Size& size, Positionf& position, Vector2D& vector) {
				int xOffset = (size.w - hitbox.w) / 2, yOffset = (size.h - hitbox.h) / 2;
				Points hitboxBounds{
					Positionf{ position.x + xOffset,position.y + yOffset },
					Positionf{ position.x + xOffset + hitbox.w ,position.y + yOffset + hitbox.h }
				};
				Positionf hitboxPosition;
				m_registry.group<>(entt::get<Hitbox, Size, Positionf>).each(
					[&](auto& entity2, Hitbox& hitbox2, Size& size2, Positionf& position2) {
						int xOffset2 = (size2.w - hitbox2.w) / 2, yOffset2 = (size2.h - hitbox2.h) / 2;
						Points hitboxBounds2{
							Positionf{ position2.x + xOffset2, position2.y + yOffset2 },
							Positionf{ position2.x + xOffset2 + hitbox2.w ,position2.y + yOffset2 + hitbox2.h }
						};

						if (entity != entity2) {
							bool xCollide = false, yCollide = false;
							if (hitboxBounds.start.x < hitboxBounds2.end.x &&
								hitboxBounds.end.x > hitboxBounds2.start.x) xCollide = true;

							if (hitboxBounds.start.y < hitboxBounds2.end.y &&
								hitboxBounds.end.y > hitboxBounds2.start.y) yCollide = true;

							if (xCollide && yCollide) {
								std::cout << "[" << hitbox.name << "] collided with [" << hitbox2.name << "]." << std::endl;
								if (xCollide) {
									position.x -= vector.x * (deltaTime / 1000);
								}
								if (yCollide) {
									position.y -= vector.y * (deltaTime / 1000);
								}

								xCollide = false, yCollide = false;
								hitboxBounds = Points{
									Positionf{ position.x + xOffset,position.y + yOffset },
									Positionf{ position.x + xOffset + hitbox.w ,position.y + yOffset + hitbox.h }
								};
								hitboxBounds2 = Points{
									Positionf{ position2.x + xOffset2, position2.y + yOffset2 },
									Positionf{ position2.x + xOffset2 + hitbox2.w ,position2.y + yOffset2 + hitbox2.h }
								};

								if (hitboxBounds.start.x < hitboxBounds2.end.x &&
									hitboxBounds.end.x > hitboxBounds2.start.x) xCollide = true;

								if (hitboxBounds.start.y < hitboxBounds2.end.y &&
									hitboxBounds.end.y > hitboxBounds2.start.y) yCollide = true;

								if (!xCollide && yCollide)
									position.y += vector.y * (deltaTime / 1000);
								if (!yCollide && xCollide )
									position.x += vector.x * (deltaTime / 1000);
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