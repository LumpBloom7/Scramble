#include "Playfield.h"
#include "Components/PlayerComponent.h"
#include "Components/Vector2D.h"
using namespace bloom::components;
void Playfield::handleInput() {

	using bloom::input::KeyboardKey;
	auto input = m_gameInstance->input;
	m_registry.group<>(entt::get<PlayerComponent, Vector2D, bloom::components::Size, Hitbox, Positionf>).each(
		[input](PlayerComponent& playerComp, Vector2D& vector, bloom::components::Size& size, Hitbox& hitbox, Positionf& position) {
			vector = Vector2D();
			if (input.keyboard.isPressed(KeyboardKey::KEY_UP))
				vector.y -= 1;
			if (input.keyboard.isPressed(KeyboardKey::KEY_DOWN))
				vector.y += 1;
			if (input.keyboard.isPressed(KeyboardKey::KEY_LEFT))
				vector.x -= 1;
			if (input.keyboard.isPressed(KeyboardKey::KEY_RIGHT))
				vector.x += 1;
			if (input.keyboard.isPressed(KeyboardKey::KEY_LEFT_SHIFT))
				playerComp.focused = true;
			else playerComp.focused = false;

			double length = std::sqrt((vector.x * vector.x) + (vector.y * vector.y));
			if (length != 0.0) {
				vector.x /= length;
				vector.y /= length;
			}

			vector.x *= playerComp.speed;
			vector.y *= playerComp.speed;
			if (playerComp.focused) { 
				if (!playerComp.wasFocused) {
					position.x += (size.w - hitbox.w) / 2;
					position.y += (size.h - hitbox.h) / 2;
					playerComp.wasFocused = true;
				}
				vector.x /= 2, vector.y /= 2;
				size = Size(25, 25);
			}
			else {
				size = Size(50, 50);
				if (playerComp.wasFocused) {
					position.x -= (size.w - hitbox.w) / 2;
					position.y -= (size.h - hitbox.h) / 2;
					playerComp.wasFocused = false;
				}
			}
		}
	);

	// Handle various input
}

void Playfield::update(double deltaTime) {
	enemyMovementSystem.update(deltaTime);
	movementSystem.update(deltaTime);
	collisionSystem.update(deltaTime);
	normalizerSystem.update();
	
}

void Playfield::draw() {
	renderSystem.update();
}


