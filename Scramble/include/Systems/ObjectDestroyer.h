#pragma once
#include "Systems/DefaultSystem.h"

#include "Components/Destroyed.h"


class ObjectDestroyer : public bloom::systems::System {
public:
	using bloom::systems::System::DefaultSystem;

	void update(double deltaTime = 0.0) {
		auto view = m_registry.view<Destroyed>();
		for (auto entity : view) {
			m_registry.destroy(entity);
		}
	}
};