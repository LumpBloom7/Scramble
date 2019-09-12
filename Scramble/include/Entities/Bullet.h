#pragma once
#include "stdIncludes.h"
#include "GameObject.h"
#include "StaticVariables.h"
#include "Components/EnemyComponent.h"
#include "Components/Vector2D.h"
#include "Components/Positionf.h"
#include "Components/Hitbox.h"
#include "Components/BulletComponent.h"

struct Bullet : public bloom::GameObject {
	Bullet(entt::registry& registry, bloom::Game*& gameInstance) : GameObject::GameObject(registry, gameInstance) {
		std::clog << "Bullet(" << m_entity << ") has been created." << std::endl;
		m_registry.assign<bloom::components::Sprite>(m_entity, c_gameInstance->textures.load(ASSETSDIR / "Assets" / "Sprites" / "Bullet.png"));
		m_registry.replace<bloom::components::Size>(m_entity, 8, 8);
		m_registry.assign<BulletComponent>(m_entity);
	}
	void init() {

	}
	void init(Positionf position, Positionf target, Hitbox::Type type) {
		m_registry.assign<Hitbox>(m_entity) = Hitbox{ Hitbox::Type::friendlyBullet,"Bullet", 8,8 };
		m_registry.assign<Positionf>(m_entity, position);

		double length = std::sqrt((target.x * target.x) + (target.y * target.y));
		if (length != 0.0) {
			target.x /= length;
			target.y /= length;
		}
		m_registry.assign<Vector2D>(m_entity, Vector2D{target.x, target.y});
	}
};