#pragma once
#include "stdIncludes.h"
#include "Components/Components.h"
#include "Components/Positionf.h"
#include "Components/Vector2D.h"
#include "Components/Speed.h"

namespace EnemyAI {
	using namespace bloom::components;
	void kamikaze(entt::registry& registry, entt::entity enemy, entt::entity player, double deltaTime = 0.0);
}