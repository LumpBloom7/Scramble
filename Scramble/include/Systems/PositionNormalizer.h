#pragma once
#include "Components/Position.h"
#include "Components/Positionf.h"
#include "Components/Destroyed.h"

namespace systems {
	static void positionNormalizerSystem(entt::registry& registry, double deltaTime = 0.0) {
		registry.group<>(entt::get<bloom::components::Position, Positionf>, entt::exclude<Destroyed>).each(
			[](auto& position, auto& positionf) {
				position.x = static_cast<int>(positionf.x + .5);
				position.y = static_cast<int>(positionf.y + .5);
			}
		);
	}
}