#include "Entities/Player.h"

void gameObjects::spawnPlayerOne(entt::registry& registry, bloom::Game*& gameInstance) {
	auto thisEntity = registry.create();
	registry.assign<Position>(thisEntity);
	registry.assign<Size>(thisEntity, 30, 34);
	registry.assign<PlayerControl>(thisEntity);
	registry.assign<Vector2D>(thisEntity);
	registry.assign<Positionf>(thisEntity);
	registry.assign<Hitbox>(thisEntity) = Hitbox{ Hitbox::Type::friendly, "Player", 30, 34 };
	registry.assign<Speed>(thisEntity) = Speed{ 200,200,200,1000, 200 };



	auto tmp = gameInstance->textures.load(ASSETSDIR / "Assets" / "Dinosaurs" / "sheets" / "Vita" / "idle.png");
	registry.assign<Sprite>(thisEntity, tmp, SDL_Rect{ 0,0,15,17 });

	// Seriously not the best way to initialize object animation.
	AnimationPtr idle{ std::make_shared<Animation>() };
	idle->animationFrames = {
		Sprite(tmp, SDL_Rect{ 0,0,15,17 }),
		Sprite(tmp, SDL_Rect{ 15,0,15,17 }),
		Sprite(tmp, SDL_Rect{ 30,0,15,17 }),
		Sprite(tmp, SDL_Rect{ 45,0,15,17 })
	};
	idle->setFrameTime(100);
	AnimationSet animSet;
	animSet.add("idle", idle);

	tmp = gameInstance->textures.load(ASSETSDIR / "Assets" / "Dinosaurs" / "sheets" / "Vita" / "walk.png");
	// Seriously not the best way to initialize object animation.
	AnimationPtr walk{ std::make_shared<Animation>() };
	walk->animationFrames = {
		Sprite(tmp, SDL_Rect{ 0,0,15,17 }),
		Sprite(tmp, SDL_Rect{ 15,0,15,17 }),
		Sprite(tmp, SDL_Rect{ 30,0,15,17 }),
		Sprite(tmp, SDL_Rect{ 45,0,15,17 }),
		Sprite(tmp, SDL_Rect{ 60,0,15,17 }),
		Sprite(tmp, SDL_Rect{ 75,0,15,17 })
	};
	walk->setFrameTime(100);
	animSet.add("walk", walk);

	registry.assign<AnimationSet>(thisEntity, animSet);
	registry.assign<AnimationPtr>(thisEntity, idle);
}
