#pragma once
#include <functional>
#include "stdIncludes.h"
#include "Components/Hitbox.h"
#include "Components/Damage.h"
#include "Components/Health.h"
#include "Components/Destroyed.h"

const std::function<void(entt::registry& registry, ColliderInfo&, ColliderInfo&)> bulletCallback = [&](entt::registry& registry, ColliderInfo& bullet, ColliderInfo& collider) {
	std::clog << " ~ Bullet callback executed" << std::endl;
	if (collider.hitbox.type == Hitbox::Type::enemy) {
		if (registry.has<Damage>(bullet.entityID) && registry.has<Health>(collider.entityID)) {
			double damage = registry.get<Damage>(bullet.entityID).value;
			double& enemyHP = registry.get<Health>(collider.entityID).amount;
			std::clog << " ~ ~ Enemy HP was " << enemyHP << std::endl;
			if (enemyHP > 0.0) {
				registry.assign<Destroyed>(bullet.entityID);
				enemyHP -= damage;
				if (enemyHP <= 0.0) {
					registry.assign<Destroyed>(collider.entityID);
				}
			}
			std::clog << " ~ ~ Enemy HP is now " << enemyHP << std::endl;
		}
	}
};