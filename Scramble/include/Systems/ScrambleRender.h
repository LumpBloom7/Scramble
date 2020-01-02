#pragma once
#include "Components/SceneContext/Camera.h"
#include "Components/Components.h"
#include "Level/Level.h"
#include "Game.h"
#include "Components/PlayerControl.h"

namespace systems {
	static void scrambleRenderSystem(bloom::Game*& gameInstance, entt::registry& registry, Tilemap& tilemap, double deltaTime = 0.0) {
		using Position = bloom::components::Position;
		using Size = bloom::components::Size;
		using Sprite = bloom::components::Sprite;
		auto& camera = registry.ctx<Camera>();

		for (Layer& layer : tilemap.layers) {
			auto spritesheet = gameInstance->textures.load(layer.tileset.path);
			int xCount = 0, yCount = 0;
			for (auto tile : layer.layerData) {
				if (tile != -1) {
					int tileSheetY = tile / tilemap.tileset.columns;
					int tileSheetX = tile - tileSheetY * tilemap.tileset.columns;
					spritesheet->render(
						SDL_Rect{ tileSheetX * tilemap.tileset.tileWidth, tileSheetY * tilemap.tileset.tileHeight,tilemap.tileset.tileWidth,tilemap.tileset.tileHeight },
						SDL_Rect{ xCount * tilemap.tileWidth,yCount * tilemap.tileHeight, tilemap.tileWidth, tilemap.tileHeight });
				}
				++xCount;
				if (xCount == tilemap.width) xCount = 0, ++yCount;
			}
			if (layer.name == "Foreground") {
				registry.group<>(entt::get<Position, Size, Sprite>).each(
					[&](auto entity, Position& position, Size& size, Sprite& sprite) {
						if (position.x + size.w > camera.xOffset
							&& position.y + size.h > camera.yOffset
							&& position.x < camera.xOffset + camera.width
							&& position.y < camera.yOffset + camera.height) {
							int hDirection = 1;
							if (registry.has<PlayerControl>(entity)) hDirection = registry.get<PlayerControl>(entity).hDirection;
							sprite.texture->render(sprite.srcRect, SDL_Rect{ position.x - camera.xOffset, position.y - camera.yOffset, size.w, size.h }, hDirection == -1 ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
						}
					}
				);
			}
		}
	}
}