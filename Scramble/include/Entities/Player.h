#pragma once
#include "stdIncludes.h"
#include "GameObject.h"
#include "StaticVariables.h"
#include "Components/PlayerComponent.h"
#include "Components/Vector2D.h"
#include "Components/Positionf.h"
#include "Components/Hitbox.h"
class PlayerObject : bloom::GameObject {
public:
	PlayerObject(entt::registry& registry, bloom::Game*& gameInstance) : GameObject::GameObject(registry, gameInstance) {
		m_registry.assign<bloom::components::Sprite>(m_entity, c_gameInstance->textures.load(ASSETSDIR / "Assets" / "Sprites" / "PlayerSprite.png"));
		m_registry.replace<bloom::components::Size>(m_entity, 50, 50);
		m_registry.assign<PlayerComponent>(m_entity);
		m_registry.assign<Vector2D>(m_entity);
		m_registry.assign<Positionf>(m_entity);
		m_registry.assign<Hitbox>(m_entity) = Hitbox{ Hitbox::Type::friendly, "Player", 10,10 };
	}

	virtual void init() {

	}

private:

};