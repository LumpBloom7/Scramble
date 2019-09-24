#include "Entities/Bullet.h"

void gameObjects::spawnBasicBullet(entt::registry& registry, bloom::Game*& gameInstance, Positionf position, Positionf target, Hitbox::Type type) {
	auto thisEntity = registry.create();
	std::clog << "Bullet(" << thisEntity << ") has been created." << std::endl;
	registry.assign<Position>(thisEntity);
	registry.assign<Sprite>(thisEntity, gameInstance->textures.load(ASSETSDIR / "Assets" / "Sprites" / "Bullet.png"));
	registry.assign<Size>(thisEntity, 8, 8);
	registry.assign<Hitbox>(thisEntity) = Hitbox{ type,"Bullet", 8, 8, 0, 0, false, bulletCallback };
	registry.assign<Speed>(thisEntity, Speed{ 300,300,300,0 });
	registry.assign<Damage>(thisEntity).value = 10;

	position.x -= 4, position.y -= 4;
	target.x = target.x + (target.x < 0 ? 4 : -4);
	target.y = target.y + (target.y < 0 ? 4 : -4);
	registry.assign<Positionf>(thisEntity, position);

	double length = std::sqrt((target.x * target.x) + (target.y * target.y));
	if (length != 0.0) {
		target.x /= length;
		target.y /= length;
	}
	registry.assign<Vector2D>(thisEntity, Vector2D{ target.x, target.y });

}
