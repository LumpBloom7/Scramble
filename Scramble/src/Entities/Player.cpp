#include "Entities/Player.h"

void gameObjects::spawnPlayerOne(entt::registry& registry, bloom::Game*& gameInstance) {
	auto thisEntity = registry.create();
	registry.assign<Position>(thisEntity);
	registry.assign<Size>(thisEntity, 48, 48);
	registry.assign<PlayerControl>(thisEntity);
	registry.assign<Vector2D>(thisEntity);
	registry.assign<Positionf>(thisEntity);
	registry.assign<Hitbox>(thisEntity) = Hitbox{ Hitbox::Type::friendly, "Player", 48, 48 };
	registry.assign<Speed>(thisEntity) = Speed{ 200,200,200,1000, 200 };



	auto tmp = gameInstance->textures.load(ASSETSDIR / "Assets" / "Dinosaurs" / "sheets" / "Vita" / "idle.png");
	registry.assign<Sprite>(thisEntity, tmp, SDL_Rect{ 0,0,24,24 });

	// Seriously not the best way to initialize object animation.
	AnimationPtr idleRight{ std::make_shared<Animation>() };
	idleRight->animationFrames = {
		Sprite(tmp, SDL_Rect{ 0,0,24,24 }),
		Sprite(tmp, SDL_Rect{ 24,0,24,24 }),
		Sprite(tmp, SDL_Rect{ 48,0,24,24 }),
		Sprite(tmp, SDL_Rect{ 72,0,24,24 })
	};
	idleRight->setFrameTime(100);
	AnimationSet animSet;
	animSet.add("idleRight", idleRight);

	AnimationPtr idleLeft{ std::make_shared<Animation>() };
	idleLeft->animationFrames = {
		Sprite(tmp, SDL_Rect{ 0,24,24,24 }),
		Sprite(tmp, SDL_Rect{ 24,24,24,24 }),
		Sprite(tmp, SDL_Rect{ 48,24,24,24 }),
		Sprite(tmp, SDL_Rect{ 72,24,24,24 })
	};

	idleLeft->setFrameTime(100);
	animSet.add("idleLeft", idleLeft);

	tmp = gameInstance->textures.load(ASSETSDIR / "Assets" / "Dinosaurs" / "sheets" / "Vita" / "walk.png");
	// Seriously not the best way to initialize object animation.
	AnimationPtr walkRight{ std::make_shared<Animation>() };
	walkRight->animationFrames = {
		Sprite(tmp, SDL_Rect{ 0,0,24,24 }),
		Sprite(tmp, SDL_Rect{ 24,0,24,24 }),
		Sprite(tmp, SDL_Rect{ 48,0,24,24 }),
		Sprite(tmp, SDL_Rect{ 72,0,24,24 }),
		Sprite(tmp, SDL_Rect{ 96,0,24,24 }),
		Sprite(tmp, SDL_Rect{ 120,0,24,24 })
	};
	walkRight->setFrameTime(100);
	animSet.add("walkRight", walkRight);

	AnimationPtr walkLeft{ std::make_shared<Animation>() };
	walkLeft->animationFrames = {
		Sprite(tmp, SDL_Rect{ 0,24,24,24 }),
		Sprite(tmp, SDL_Rect{ 24,24,24,24 }),
		Sprite(tmp, SDL_Rect{ 48,24,24,24 }),
		Sprite(tmp, SDL_Rect{ 72,24,24,24 }),
		Sprite(tmp, SDL_Rect{ 96,24,24,24 }),
		Sprite(tmp, SDL_Rect{ 120,24,24,24 })
	};
	walkLeft->setFrameTime(100);
	animSet.add("walkLeft", walkLeft);

	registry.assign<AnimationSet>(thisEntity, animSet);
	registry.assign<AnimationPtr>(thisEntity, idleRight);
}
