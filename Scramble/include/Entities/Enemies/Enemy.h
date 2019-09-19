#pragma once
#include "stdIncludes.h"
#include "GameObject.h"
#include "StaticVariables.h"
#include "Components/EnemyComponent.h"
#include "Components/Vector2D.h"
#include "Components/Positionf.h"
#include "Components/Hitbox.h"

class Enemy : bloom::GameObject {
public:
	Enemy(entt::registry& registry, bloom::Game*& gameInstance) : bloom::GameObject::GameObject(registry, gameInstance) {
		std::clog << "Enemy(" << m_entity << ") has been created." << std::endl;
		m_registry.assign<bloom::components::Sprite>(m_entity, c_gameInstance->textures.load(ASSETSDIR / "Assets" / "Sprites" / "Enemy.png"));
		m_registry.replace<bloom::components::Size>(m_entity, 50, 50);
		m_registry.assign<Vector2D>(m_entity);
		m_registry.assign<Positionf>(m_entity) = Positionf{ 375, 275 };
		m_registry.assign<Hitbox>(m_entity) = Hitbox{ Hitbox::Type::enemy,"Enemy", 50,50 };
		m_registry.assign<EnemyComponent>(m_entity) = EnemyComponent{ EnemyComponent::EnemyType::solid };
	}

	void init() {}
private:
};
