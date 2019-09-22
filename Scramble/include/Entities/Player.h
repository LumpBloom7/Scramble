#pragma once
#include "stdIncludes.h"
#include "GameObject.h"
#include "StaticVariables.h"
#include "Components/PlayerControl.h"
#include "Components/Vector2D.h"
#include "Components/Positionf.h"
#include "Components/Hitbox.h"
#include "Components/Speed.h"
class PlayerObject : bloom::GameObject {
public:
	PlayerObject(entt::registry& registry, bloom::Game*& gameInstance) : GameObject::GameObject(registry, gameInstance) {
		m_registry.assign<bloom::components::Sprite>(m_entity, c_gameInstance->textures.load(ASSETSDIR / "Assets" / "Sprites" / "PlayerSprite.png"));
		m_registry.replace<bloom::components::Size>(m_entity, 50, 50);
		m_registry.assign<PlayerControl>(m_entity);
		m_registry.assign<Vector2D>(m_entity);
		m_registry.assign<Positionf>(m_entity);
		m_registry.assign<Hitbox>(m_entity) = Hitbox{ Hitbox::Type::friendly, "Player", 10, 10 };
		m_registry.assign<Speed>(m_entity) = Speed{ 600,600,600,600, 200 };
	}

	virtual void init() { }

private:

};