#pragma once
#include "Components/Destroyed.h"

namespace systems {
	static void objectDestroyerSystem(entt::registry& registry, double deltaTime = 0.0) {
		auto view = registry.view<Destroyed>();
		for (auto entity : view) {
			registry.destroy(entity);
			std::clog << "Entity " << entity << " has been destroyed." << std::endl;
		}
	}
};