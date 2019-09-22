#pragma once
#include <deque>
#include "entt/entt.hpp"
#include "Game.h"
#include "Systems/Systems.h"
#include "Systems/MovementSystem.h"
#include "Systems/PositionNormalizer.h"
#include "Systems/EnemyBehavior.h"
#include "Systems/CollisionSystem.h"
#include "Entities/Player.h"
#include "Entities/Bullet.h"
#include "Entities/Enemies/Enemy.h"
#include "Entities/Enemies/Kamikaze.h"

class Playfield {
public:
	Playfield(bloom::Game*& gameInstance) : m_gameInstance(gameInstance) {}
	void handleInput(double deltaTime = 0.0);
	void update(double deltaTime = 0.0);
	void draw();

private:
	entt::registry m_registry;
	bloom::Game*& m_gameInstance;

	bloom::systems::RenderSystem renderSystem = bloom::systems::RenderSystem(m_registry);
	MovementSystem movementSystem = MovementSystem(m_registry);
	PositionNormalizer normalizerSystem = PositionNormalizer(m_registry);
	EnemyBehavior enemyMovementSystem = EnemyBehavior(m_registry);
	CollisionSystem collisionSystem = CollisionSystem(m_registry);
	PlayerObject player = PlayerObject(m_registry, m_gameInstance);
	EnemyObject enemy = EnemyObject(m_registry, m_gameInstance);
	Kamikaze kamikaze = Kamikaze(m_registry, m_gameInstance);

	std::deque<Bullet> bullets;
	double m_dt = 200.0;

};
