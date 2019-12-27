#include "Entities/Player.h"

void gameObjects::spawnPlayerOne(entt::registry& registry, bloom::Game*& gameInstance) {
	auto thisEntity = registry.create();
	registry.assign<Position>(thisEntity);
	registry.assign<Size>(thisEntity, 48, 48);
	registry.assign<PlayerControl>(thisEntity);
	registry.assign<Vector2D>(thisEntity);
	registry.assign<Positionf>(thisEntity);
	registry.assign<Hitbox>(thisEntity) = Hitbox{ Hitbox::Type::friendly, "Player", 48, 48 };
	registry.assign<Speed>(thisEntity) = Speed{ 600,600,600,600, 200 };


	auto tmp = gameInstance->textures.load(ASSETSDIR / "Assets" / "Dinosaurs" / "sheets" / "DinoSprites - vita.png");
	registry.assign<Sprite>(thisEntity, tmp, SDL_Rect{ 0,0,24,24 });

	// Seriously not the best way to initialize object animation.
	AnimationPtr idle{ std::make_shared<Animation>() };
	idle->animationFrames = {
		Sprite(tmp, SDL_Rect{ 0,0,24,24 }),
		Sprite(tmp, SDL_Rect{ 24,0,24,24 }),
		Sprite(tmp, SDL_Rect{ 48,0,24,24 }),
		Sprite(tmp, SDL_Rect{ 72,0,24,24 })
	};
	idle->setFrameTime(250);
	AnimationSet animSet;
	animSet.add("idle", idle);
	

	registry.assign<AnimationSet>(thisEntity, animSet);
	registry.assign<AnimationPtr>(thisEntity, idle);
}
