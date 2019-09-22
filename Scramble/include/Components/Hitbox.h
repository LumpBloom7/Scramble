#pragma once
#include "Components/Size.h"
#include "Components/Positionf.h"

struct Grid {
	int x = 0, y = 0;
};

struct Points {
	Positionf start, end;
};

struct Hitbox;

struct ColliderInfo {
	using Position = bloom::components::Position;
	using Size = bloom::components::Size;

	ColliderInfo(entt::entity e, Hitbox& h, Size& s, Positionf& p, Points hb) : entityID(e), hitbox(h), size(s), position(p), hitboxBounds(hb) {}
	entt::entity entityID;
	Hitbox& hitbox;
	Size& size;
	Positionf& position;
	Points hitboxBounds;
};

struct Hitbox {
	enum class Type {
		friendly,
		enemy,
		friendlyBullet,
		enemyBullet
	} type;

	std::string name = "Object";
	double w, h;
	double xOffset, yOffset;
	bool solid = true;
	std::function<void(entt::registry& registry, ColliderInfo&, ColliderInfo&)> callback = [&](entt::registry& registry, ColliderInfo& first, ColliderInfo& second) {std::clog << "~ Callback is executed, but it doesn't do anything." << std::endl;};

	std::vector<Grid> intersectedGrids;
};

