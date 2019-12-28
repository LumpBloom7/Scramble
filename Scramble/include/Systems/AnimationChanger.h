#pragma once
#include "Components/Vector2D.h"
#include "Components/Components.h"
#include "Components/Positionf.h"
#include "Components/Speed.h"
#include "Components/PlayerControl.h"
//#include "Components/Enemy.h"
#include "Components/Destroyed.h"
#include "Components/Hitbox.h"
#include "Components/AnimationSet.h"

namespace systems {
	static void animationChangerSystem(entt::registry& registry, double deltaTime = 0.0) {
		deltaTime /= 1000.0;
		registry.group<>(entt::get<PlayerControl, Vector2D, bloom::components::AnimationSet>, entt::exclude<Destroyed>).each(
			[&](auto& entity,PlayerControl& player, Vector2D& vector, bloom::components::AnimationSet& animSet) {
				std::string animName;

				if (vector.x != 0 || vector.y != 0)
					animName = "walk";
				else
					animName = "idle";

				if (player.hDirection == -1)
					animName += "Left";
				else if (player.hDirection == 1)
					animName += "Right";

				animSet.changeCurrent(animName);
			}
		);
	}
}
#pragma once
