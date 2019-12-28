#include "Framework.h"
#include "entt/entt.hpp"
#include "Playfield.h"
using namespace bloom;

Game* game = nullptr;

int main(int argc, char* argv[]) {
	try {
		Game::initialize();
	}
	catch (Exception & e) {
		std::cerr << e.what() << std::endl;
		system("pause");
		exit(-1);
	}

	game = new Game({ 800, 600 }, { 0, SDL_RENDERER_TARGETTEXTURE });
	try {
		game->create("Scramble!!", { SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED });
	}
	catch (Exception & e) {
		std::cerr << e.what() << std::endl;
	}

	SDL_DisplayMode dm;
	SDL_GetCurrentDisplayMode(0, &dm);
	std::cout << "Screen width is " << dm.w << ", screen height is " << dm.h << "." << std::endl;

	srand(static_cast<uint32_t>(time(nullptr)));
	SDL_Color randColor = { 255, 0, 255 };
	game->setColor(randColor);
	game->clear();
	game->render();

	Playfield playfield(game, ASSETSDIR / "Assets" / "Level1" / "Tilemap.txt");
	SDL_ShowCursor(SDL_DISABLE);
	game->timer.restart();
	while (game->isRunning()) {
		double dt = game->timer.lap();
		game->clear();
		game->handleEvents();
		playfield.handleInput(dt);
		playfield.update(dt);
		playfield.draw();
		game->render();
	}
	return 0;
}