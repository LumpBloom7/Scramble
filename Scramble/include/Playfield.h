#pragma once
#include <deque>
#include <string>
#include "entt/entt.hpp"
#include "Game.h"
#include "Systems/Systems.h"
#include "Systems/MovementSystem.h"
#include "Systems/PositionNormalizer.h"
//#include "Systems/EnemyBehavior.h"
#include "Systems/CollisionSystem.h"
#include "Systems/ObjectDestroyer.h"
#include "Systems/ScrambleRender.h"
#include "Systems/CameraMovement.h"
#include "Systems/AnimationChanger.h"
#include "Entities/Player.h"
#include "Entities/Bullet.h"
//#include "Entities/Enemy.h" Removed for now
#include "Components/SceneContext/Camera.h"
#include "Graphics/SpriteText.h"
#include "Graphics/Font.h"
#include "Graphics/FontStore.h"
#include "Level/Level.h"

using namespace bloom::graphics;
const bloom::graphics::FontStyle defaultFontStyle{ 20 };
const bloom::graphics::TextStyle defaultTextStyle{ TextStyle::BlendingMode::blended };

class Playfield {
public:
	Playfield(bloom::Game*& gameInstance, std::filesystem::path tilemapPath) : m_gameInstance(gameInstance) {
		m_registry.set<Camera>(Camera{ 0, 0 });
		gameObjects::spawnPlayerOne(m_registry, gameInstance);
		//gameObjects::spawnBasicEnemy(m_registry, gameInstance);
		//gameObjects::spawnKamikaze(m_registry, gameInstance);
		fontStore.load(ASSETSDIR / "Assets" / "Fonts" / "Cascadia.ttf", 0, defaultFontStyle);
		text.emplace("cameraInfo", std::make_shared<SpriteText>(m_gameInstance->_getRenderer(), fontStore[0], "0x0", defaultTextStyle));
		text.emplace("playerInfo", std::make_shared<SpriteText>(m_gameInstance->_getRenderer(), fontStore[0], "0x1", defaultTextStyle));
		tilemap = generateTilemap(tilemapPath);

	}
	void handleInput(double deltaTime = 0.0);
	void update(double deltaTime = 0.0);
	void draw();

private:
	Tilemap tilemap;
	entt::registry m_registry;
	bloom::Game*& m_gameInstance;
	bloom::graphics::FontStore fontStore;
	std::unordered_map<std::string, std::shared_ptr<SpriteText>> text;
	bloom::systems::AnimationSystem animSys = bloom::systems::AnimationSystem(m_registry);

	double m_dt = 200.0;
};
