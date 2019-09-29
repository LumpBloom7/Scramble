#pragma once
#include "Components/SceneContext/Camera.h"
#include "Components/Components.h"

namespace systems {
	static void scrambleRenderSystem(entt::registry& registry, double deltaTime = 0.0) {
		using Position = bloom::components::Position;
		using Size = bloom::components::Size;
		using Sprite = bloom::components::Sprite;
		auto& camera = registry.ctx<Camera>();

		registry.group<>(entt::get<Position, Size, Sprite>).each(
			[&](auto, Position& position, Size& size, Sprite& sprite) {
				if (position.x + size.w > camera.xOffset
					&& position.y + size.h > camera.yOffset
					&& position.x < camera.xOffset + camera.width
					&& position.y < camera.yOffset + camera.height)
					sprite.texture->render(sprite.srcRect, SDL_Rect{ position.x - camera.xOffset, position.y - camera.yOffset, size.w, size.h });
			}
		);
	}
}