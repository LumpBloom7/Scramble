#include "Playfield.h"
#include "Components/PlayerControl.h"
#include "Components/Vector2D.h"
using namespace bloom::components;
void Playfield::handleInput(double deltaTime) {
	using bloom::input::MouseButton;
	using bloom::input::KeyboardKey;
	auto input = m_gameInstance->input;
	m_dt -= deltaTime;
	auto& camera = m_registry.ctx<Camera>();
	m_registry.group<>(entt::get<PlayerControl, Vector2D, bloom::components::Size, Hitbox, Positionf, Speed>).each(
		[&](PlayerControl& playerComp, Vector2D& vector, bloom::components::Size& size, Hitbox& hitbox, Positionf& position, Speed& speed) {
			vector = Vector2D();
			if (input.keyboard.isPressed(KeyboardKey::KEY_UP))
				vector.y -= 1;
			if (input.keyboard.isPressed(KeyboardKey::KEY_DOWN))
				vector.y += 1;
			if (input.keyboard.isPressed(KeyboardKey::KEY_LEFT))
				vector.x -= 1, playerComp.hDirection = -1;
			if (input.keyboard.isPressed(KeyboardKey::KEY_RIGHT))
				vector.x += 1, playerComp.hDirection = 1;
			if (input.keyboard.isPressed(KeyboardKey::KEY_LEFT_SHIFT))
				playerComp.focused = true;
			else playerComp.focused = false;

			double length = std::sqrt((vector.x * vector.x) + (vector.y * vector.y));
			if (length != 0.0) {
				vector.x /= length;
				vector.y /= length;
			}
			/*if (playerComp.focused) {
				if (!playerComp.wasFocused) {
					sprite = bloom::graphics::Sprite(m_gameInstance->textures.load(ASSETSDIR / "Assets" / "Sprites" / "PlayerSpriteFocused.png"));
					playerComp.wasFocused = true;
				}
				speed.xValue = 300;
				speed.yValue = 300;
			}
			else {
				if (playerComp.wasFocused) {
					sprite = bloom::graphics::Sprite(m_gameInstance->textures.load(ASSETSDIR / "Assets" / "Sprites" / "PlayerSprite.png"));
					playerComp.wasFocused = false;
				}
				speed.xValue = 600;
				speed.yValue = 600;
			}*/

			if (input.mouse.isPressed(MouseButton::MOUSE_LEFT) && m_dt <= 0.0) {
				Positionf spawn{ position.x + size.w / 2, position.y + size.h / 2 };
				Positionf target{ input.mouse.getX() - spawn.x + camera.xOffset, input.mouse.getY() - spawn.y + camera.yOffset };
				gameObjects::spawnBasicBullet(m_registry, m_gameInstance, spawn, target, Hitbox::Type::friendlyBullet);
				m_dt = 200.0;
			}
		}
	);
}

void Playfield::update(double deltaTime) {
	//systems::enemyBehaviorSystem(m_registry, deltaTime);
	systems::movementSystem(m_registry, tilemap, deltaTime);
	systems::collisionSystem(m_registry, deltaTime);
	systems::objectDestroyerSystem(m_registry);
	systems::positionNormalizerSystem(m_registry);
	//systems::cameraMovementSystem(m_registry);
	systems::animationChangerSystem(m_registry);
	animSys.update(deltaTime);
}

void Playfield::draw() {
	systems::scrambleRenderSystem(m_gameInstance,m_registry,tilemap);
	auto input = m_gameInstance->input;
	m_gameInstance->textures.load(ASSETSDIR / "Assets" / "Sprites" / "Crosshair32.png")->render(std::nullopt, { input.mouse.getX() - 16, input.mouse.getY() - 16, 32, 32 });

	auto& camera = m_registry.ctx<Camera>();
	auto& playerPos = m_registry.get<Position>(m_registry.view<PlayerControl>()[0]);
	text["cameraInfo"]->setText("Camera Offset  : { " + std::to_string(camera.xOffset) + ", " + std::to_string(camera.yOffset) + " }");
	text["cameraInfo"]->render(std::nullopt, SDL_Point{ 0,0 });
	text["playerInfo"]->setText("Player position: { " + std::to_string(playerPos.x) + ", " + std::to_string(playerPos.y) + " } / { " + std::to_string(playerPos.x - camera.xOffset) + ", " + std::to_string(playerPos.y - camera.yOffset) + " }");
	text["playerInfo"]->render(std::nullopt, SDL_Point{ 0,20 });
}


