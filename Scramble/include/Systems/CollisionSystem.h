#pragma once
#include "Components/Hitbox.h"
#include "Components/Size.h"
#include "Components/Position.h"
#include "Components/PlayerControl.h"
#include "Components/Enemy.h"
#include "Components/Destroyed.h"

namespace systems {
	static void collisionSystem(entt::registry& registry, double deltaTime = 0.0) {
		using Position = bloom::components::Position;
		using Size = bloom::components::Size;
		std::unordered_map<entt::entity, std::vector<Grid>> intersectMap{};
		std::unordered_map<int, std::unordered_map<int, std::vector<ColliderInfo>>> uniformGrid{};

		registry.group<>(entt::get<Hitbox, Size, Positionf>, entt::exclude<Destroyed>).each(
			[&](auto& entity, Hitbox& hitbox, Size& size, Positionf& position) {
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
						intersectMap[entity].emplace_back(Grid{ i,j });
					}
			}
		);
		registry.group<>(entt::get<Hitbox, Size, Positionf, Vector2D, Speed>).each(
			[&](auto& entity, Hitbox& hitbox, Size& size, Positionf& position, Vector2D& vector, Speed& speed) {
				int xOffset = static_cast<int>((size.w - hitbox.w) / 2), yOffset = static_cast<int>((size.h - hitbox.h) / 2);
				Points hitboxBounds{
					Positionf{ position.x + xOffset,position.y + yOffset },
					Positionf{ position.x + xOffset + hitbox.w ,position.y + yOffset + hitbox.h }
				};
				ColliderInfo info(entity, hitbox, size, position, hitboxBounds);
				std::unordered_map<entt::entity, bool> processed{};
				for (auto& grid : intersectMap[entity]) {
					for (auto& collider : uniformGrid[grid.x][grid.y]) {
						if (entity != collider.entityID && !processed[collider.entityID] && !registry.has<Destroyed>(collider.entityID) && !registry.has<Destroyed>(entity)) {
							processed[collider.entityID] = true;
							bool xCollide = false, yCollide = false;
							if (hitboxBounds.start.x < collider.hitboxBounds.end.x &&
								hitboxBounds.end.x > collider.hitboxBounds.start.x) xCollide = true;

							if (hitboxBounds.start.y < collider.hitboxBounds.end.y &&
								hitboxBounds.end.y > collider.hitboxBounds.start.y) yCollide = true;

							if (xCollide && yCollide) {
								std::cout << "[" << hitbox.name << "](" << entity << ") collided with [" << collider.hitbox.name << "](" << collider.entityID << ")." << std::endl;
								hitbox.callback(registry, info, collider);
								if (hitbox.solid && collider.hitbox.solid) {
									if (xCollide) {
										position.x -= (vector.x * speed.xValue) * (deltaTime / 1000);
									}
									if (yCollide) {
										position.y -= (vector.y * speed.yValue) * (deltaTime / 1000);
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
										position.y += (vector.y * speed.xValue) * (deltaTime / 1000);
									if (!yCollide && xCollide)
										position.x += (vector.x * speed.yValue) * (deltaTime / 1000);
								}
							}
						}
					}
				}
			}
		);
	}
}