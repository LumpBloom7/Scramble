#pragma once
#include "stdIncludes.h"
#include "Components/SceneContext/Camera.h"
#include "Components/PlayerControl.h"
#include "Components/Positionf.h"

namespace systems {
	static void cameraMovementSystem(entt::registry& registry, double deltaTime = 0.0) {
		auto& camera = registry.ctx<Camera>();
		auto& playerEnt = registry.get<Positionf>(registry.group<>(entt::get<PlayerControl, Positionf>)[0]);
		int horizontalMove = playerEnt.x - (camera.xOffset + camera.width / 2);
		if (horizontalMove >= 160)
			horizontalMove -= 160;
		else if (horizontalMove <= -160)
			horizontalMove += 160;
		else
			horizontalMove = 0;

		int verticalMove = playerEnt.y - (camera.yOffset + camera.height / 2);
		if (verticalMove >= 120)
			verticalMove -= 120;
		else if (verticalMove <= -120)
			verticalMove += 120;
		else
			verticalMove = 0;

		camera.xOffset += horizontalMove;
		camera.yOffset += verticalMove;

	}
}