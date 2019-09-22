#pragma once
#include "Systems/DefaultSystem.h"
#include "Components/Position.h"
#include "Components/Positionf.h"
#include "Components/Destroyed.h"


class PositionNormalizer : public bloom::systems::System {
public:
	using bloom::systems::System::DefaultSystem;

	void update(double deltaTime = 0.0) {
		m_registry.group<>(entt::get<bloom::components::Position, Positionf>, entt::exclude<Destroyed>).each(
			[](auto& position, auto& positionf) {
				position.x = static_cast<int>(positionf.x + .5);
				position.y = static_cast<int>(positionf.y + .5);
			}
		);
	}
};