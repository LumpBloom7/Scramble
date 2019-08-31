#include "Playfield.h"
#include "Components/PlayerComponent.h"
#include "Components/Vector2D.h"
using namespace bloom::components;
void Playfield::handleInput() {
	
	using bloom::input::KeyboardKey;
	auto input = m_gameInstance->input;
	m_registry.group<>(entt::get<PlayerComponent, Vector2D>).each(
		[input](PlayerComponent& playerComp, Vector2D& vector) {
			if (input.keyboard.isPressed(KeyboardKey::KEY_UP))
				vector.y -= 1;
			if (input.keyboard.isPressed(KeyboardKey::KEY_DOWN))
				vector.y += 1;
			if (input.keyboard.isPressed(KeyboardKey::KEY_LEFT))
				vector.x -= 1;
			if (input.keyboard.isPressed(KeyboardKey::KEY_RIGHT))
				vector.x += 1;
		}
	);

	// Handle various input
}

void Playfield::update() {
	movementSystem.update();
}

void Playfield::draw() {
	renderSystem.update();
}


