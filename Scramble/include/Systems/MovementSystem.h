#pragma once
#include "Components/Vector2D.h"
#include "Components/Components.h"
#include "Components/Positionf.h"
#include "Components/Speed.h"
#include "Components/PlayerControl.h"
#include "Components/Enemy.h"
#include "Components/Destroyed.h"
#include "Components/Hitbox.h"

namespace systems {
	static void movementSystem(entt::registry& registry, double deltaTime = 0.0) {
		deltaTime /= 1000.0;
		registry.group<>(entt::get<Vector2D, Positionf, Speed, bloom::components::Size>, entt::exclude<Destroyed>).each(
			[&](auto& entity, Vector2D& vector, Positionf& position, Speed& speed, bloom::components::Size& size) {
				position.x += vector.x * std::abs(speed.xValue) * deltaTime;
				position.y += vector.y * std::abs(speed.yValue) * deltaTime;

				if (registry.has<PlayerControl>(entity)) {
					auto& size = registry.get<bloom::components::Size>(entity);
					if (position.x < 0) position.x = 0.0;
					else if (position.x > static_cast<double>(800) - size.w) position.x = static_cast<double>(800) - size.w;
					if (position.y < 0) position.y = 0.0;
					else if (position.y > static_cast<double>(600) - size.h) position.y = static_cast<double>(600) - size.h;
				}
				if (registry.has<Hitbox>(entity)) {
					if (registry.get<Hitbox>(entity).type == Hitbox::Type::friendlyBullet) {
						if (position.x < -200) registry.assign<Destroyed>(entity);
						else if (position.x > static_cast<double>(1000)) registry.assign<Destroyed>(entity);
						if (position.y < -200) registry.assign<Destroyed>(entity);
						else if (position.y > static_cast<double>(800)) registry.assign<Destroyed>(entity);
					}
				}
			}
		);
	}
}
