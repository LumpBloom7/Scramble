#include "Framework.h"
#include "entt/entt.hpp"
using namespace bloom;

Game* game = nullptr;

int main(int argc, char* argv[]) {
	game = new Game({ 800, 600 }, { 0, 0 | SDL_RENDERER_TARGETTEXTURE });
	try {
		game->create("Scramble!!", { SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED });
	}
	catch (Exception& e) {
		std::cerr << e.what() << std::endl;
	}

	SDL_DisplayMode dm;
	SDL_GetCurrentDisplayMode(0, &dm);
	std::cout << "Screen width is " << dm.w << ", screen height is " << dm.h << "." << std::endl;

	srand(static_cast<uint32_t>(time(nullptr)));
	SDL_Color randColor = { static_cast<Uint8>(rand() % 255), static_cast<Uint8>(rand() % 255),
		static_cast<Uint8>(rand() % 255), static_cast<Uint8>(rand() % 255) };
	game->setColor(randColor);
	game->clear();
	game->render();

	system("pause");
	return 0;
}