#pragma once
#include "stdIncludes.h"
#include "GameObject.h"
#include "StaticVariables.h"
#include "Components/Enemy.h"
#include "Components/Vector2D.h"
#include "Components/Positionf.h"
#include "Components/Hitbox.h"
#include "Components/Speed.h"
#include "Components/Damage.h"
#include "Callbacks/Hitbox/BulletCallback.h"

namespace gameObjects {
	using namespace bloom::components;
	void spawnBasicBullet(entt::registry& registry, bloom::Game*& gameInstance, Positionf position, Positionf target, Hitbox::Type type);
}