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

struct ColliderInfo {
	using Position = bloom::components::Position;
	using Size = bloom::components::Size;

	ColliderInfo(entt::entity e, Hitbox& h, Size& s, Positionf& p, Points hb) : entityID(e), hitbox(h), size(s), position(p), hitboxBounds(hb) {}
	entt::entity entityID;
	Hitbox& hitbox;
	Size& size;
	Positionf& position;
	Points hitboxBounds;
};

class CollisionSystem : public bloom::systems::System {
public:
	using bloom::systems::System::DefaultSystem;
	using Position = bloom::components::Position;
	using Size = bloom::components::Size;

	void update(double deltaTime = 0.0) {
		timeDifference += deltaTime;
		std::unordered_map<int, std::unordered_map<int, std::vector<ColliderInfo>>> uniformGrid{};

		m_registry.view<Hitbox, Size, Positionf>().each(
			[&](auto& entity, Hitbox& hitbox, Size& size, Positionf& position) {
				hitbox.intersectedGrids.clear();
				int xOffset = static_cast<int>((size.w - hitbox.w) / 2), yOffset = static_cast<int>((size.h - hitbox.h) / 2);
				Points hitboxBounds{
					Positionf{ position.x + xOffset,position.y + yOffset },
					Positionf{ position.x + xOffset + hitbox.w ,position.y + yOffset + hitbox.h }
				};
				Grid one{ static_cast<int>(hitboxBounds.start.x / 8), static_cast<int>(hitboxBounds.start.y / 8) }, two{ static_cast<int>(hitboxBounds.end.x / 8), static_cast<int>(hitboxBounds.end.y / 8) };
				for (int i = one.x; i <= two.x; ++i)
					for (int j = one.y; j <= two.y; ++j) {
						ColliderInfo info(entity, hitbox, size, position, hitboxBounds);
						uniformGrid[i][j].emplace_back(info);
						hitbox.intersectedGrids.emplace_back(Grid{ i,j });
					}
			}
		);
		m_registry.view<Hitbox, Size, Positionf, Vector2D>().each(
			[&](auto& entity, Hitbox& hitbox, Size& size, Positionf& position, Vector2D& vector) {
				int xOffset = static_cast<int>((size.w - hitbox.w) / 2), yOffset = static_cast<int>((size.h - hitbox.h) / 2);
				Points hitboxBounds{
					Positionf{ position.x + xOffset,position.y + yOffset },
					Positionf{ position.x + xOffset + hitbox.w ,position.y + yOffset + hitbox.h }
				};
				std::unordered_map<entt::entity, bool> processed{};
				for (auto& grid : hitbox.intersectedGrids) {
					for (auto& collider : uniformGrid[grid.x][grid.y]) {
						if (entity != collider.entityID && !processed[collider.entityID] && (collider.hitbox.type != Hitbox::Type::friendlyBullet && hitbox.type != Hitbox::Type::friendlyBullet)) {
							processed[collider.entityID] = true;
							bool xCollide = false, yCollide = false;
							if (hitboxBounds.start.x < collider.hitboxBounds.end.x &&
								hitboxBounds.end.x > collider.hitboxBounds.start.x) xCollide = true;

							if (hitboxBounds.start.y < collider.hitboxBounds.end.y &&
								hitboxBounds.end.y > collider.hitboxBounds.start.y) yCollide = true;

							if (xCollide && yCollide) {
								std::cout << "[" << hitbox.name << "](" << entity << ") collided with [" << collider.hitbox.name << "](" << collider.entityID << ")." << std::endl;
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

								if (hitboxBounds.start.x < collider.hitboxBounds.end.x &&
									hitboxBounds.end.x > collider.hitboxBounds.start.x) xCollide = true;

								if (hitboxBounds.start.y < collider.hitboxBounds.end.y &&
									hitboxBounds.end.y > collider.hitboxBounds.start.y) yCollide = true;

								if (!xCollide && yCollide)
									position.y += vector.y * (deltaTime / 1000);
								if (!yCollide && xCollide)
									position.x += vector.x * (deltaTime / 1000);
							}
						}
					}
				}
			}
		);
	}

private:
	double timeDifference = 0.0;
};