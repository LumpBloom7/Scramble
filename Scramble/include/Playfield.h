#pragma once
#include "entt/entt.hpp"
#include "Game.h"
#include "Systems/Systems.h"
#include "Systems/PlayerMovement.h"
#include "Systems/PositionNormalizer.h"
#include "Entities/Player.h"

class Playfield {
public:
	Playfield(bloom::Game*& gameInstance) : m_gameInstance(gameInstance) {
		
	}
	void handleInput();
	void update(double deltaTime = 0.0);
	void draw();

private:
	entt::registry m_registry;
	bloom::Game*& m_gameInstance;

	bloom::systems::RenderSystem renderSystem = bloom::systems::RenderSystem(m_registry);
	MovementHandler movementSystem = MovementHandler(m_registry);
	PositionNormalizer normalizerSystem = PositionNormalizer(m_registry);
	PlayerObject player = PlayerObject(m_registry, m_gameInstance);
};
