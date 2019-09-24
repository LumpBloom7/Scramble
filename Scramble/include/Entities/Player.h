#pragma once
#include "stdIncludes.h"
#include "GameObject.h"
#include "StaticVariables.h"
#include "Components/PlayerControl.h"
#include "Components/Vector2D.h"
#include "Components/Positionf.h"
#include "Components/Hitbox.h"
#include "Components/Speed.h"

namespace gameObjects {
	using namespace bloom::components;
	void spawnPlayerOne(entt::registry& registry, bloom::Game*& gameInstance);
}