#pragma once
#include "stdIncludes.h"
#include "GameObject.h"
#include "StaticVariables.h"
#include "Components/Enemy.h"
#include "Components/Vector2D.h"
#include "Components/Positionf.h"
#include "Components/Hitbox.h"
#include "Components/Speed.h"
#include "Components/Health.h"

namespace gameObjects {
	using namespace bloom::components;
	void spawnBasicEnemy(entt::registry& registry, bloom::Game*& gameInstance);

	void spawnKamikaze(entt::registry& registry, bloom::Game*& gameInstance);
}