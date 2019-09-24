#include "Entities/Player.h"

void gameObjects::spawnPlayerOne(entt::registry& registry, bloom::Game*& gameInstance) {
	auto thisEntity = registry.create();
	registry.assign<Position>(thisEntity);
	registry.assign<Sprite>(thisEntity, gameInstance->textures.load(ASSETSDIR / "Assets" / "Sprites" / "PlayerSprite.png"));
	registry.assign<Size>(thisEntity, 50, 50);
	registry.assign<PlayerControl>(thisEntity);
	registry.assign<Vector2D>(thisEntity);
	registry.assign<Positionf>(thisEntity);
	registry.assign<Hitbox>(thisEntity) = Hitbox{ Hitbox::Type::friendly, "Player", 10, 10 };
	registry.assign<Speed>(thisEntity) = Speed{ 600,600,600,600, 200 };
}
