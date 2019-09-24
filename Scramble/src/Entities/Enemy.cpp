#include "Entities/Enemy.h"

void gameObjects::spawnBasicEnemy(entt::registry& registry, bloom::Game*& gameInstance) {
	auto thisEntity = registry.create();
	registry.assign<Position>(thisEntity);
	registry.assign<Sprite>(thisEntity, gameInstance->textures.load(ASSETSDIR / "Assets" / "Sprites" / "Enemy.png"));
	registry.assign<Size>(thisEntity, 50, 50);
	registry.assign<Vector2D>(thisEntity);
	registry.assign<Positionf>(thisEntity) = Positionf{ 375, 275 };
	registry.assign<Hitbox>(thisEntity) = Hitbox{ Hitbox::Type::enemy,"Enemy", 50,50 };
	registry.assign<Enemy>(thisEntity) = Enemy{ Enemy::EnemyType::solid };
}

void gameObjects::spawnKamikaze(entt::registry& registry, bloom::Game*& gameInstance) {
	auto thisEntity = registry.create();
	std::clog << "Kamikaze(" << thisEntity << ") has been created." << std::endl;
	registry.assign<Position>(thisEntity);
	registry.assign<Sprite>(thisEntity, gameInstance->textures.load(ASSETSDIR / "Assets" / "Sprites" / "Kamikaze.png"));
	registry.assign<Size>(thisEntity, 50, 50);
	registry.assign<Vector2D>(thisEntity);
	registry.assign<Positionf>(thisEntity) = Positionf{ 750, 550 };
	registry.assign<Hitbox>(thisEntity) = Hitbox{ Hitbox::Type::enemy,"Enemy", 50, 50 };
	registry.assign<Enemy>(thisEntity) = Enemy{ Enemy::EnemyType::kamikaze, 100 };
	registry.assign<Speed>(thisEntity) = Speed{ 500.0,300,300, 1, 1 };
	registry.assign<Health>(thisEntity).amount = 100.0;
}
