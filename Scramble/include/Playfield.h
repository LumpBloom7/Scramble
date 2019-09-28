#pragma once
#include <deque>
#include "entt/entt.hpp"
#include "Game.h"
#include "Systems/Systems.h"
#include "Systems/MovementSystem.h"
#include "Systems/PositionNormalizer.h"
#include "Systems/EnemyBehavior.h"
#include "Systems/CollisionSystem.h"
#include "Systems/ObjectDestroyer.h"
#include "Entities/Player.h"
#include "Entities/Bullet.h"
#include "Entities/Enemy.h"

class Playfield {
public:
	Playfield(bloom::Game*& gameInstance) : m_gameInstance(gameInstance) {
		gameObjects::spawnPlayerOne(m_registry, gameInstance);
		gameObjects::spawnBasicEnemy(m_registry, gameInstance);
		gameObjects::spawnKamikaze(m_registry, gameInstance);
	}
	void handleInput(double deltaTime = 0.0);
	void update(double deltaTime = 0.0);
	void draw();

private:
	entt::registry m_registry;
	bloom::Game*& m_gameInstance;

	bloom::systems::RenderSystem renderSystem = bloom::systems::RenderSystem(m_registry);

	double m_dt = 200.0;

};
