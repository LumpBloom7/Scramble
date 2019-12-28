#include "Level/Level.h"

Tilemap generateTilemap(std::filesystem::path tilemapPath) {
	Tilemap test;

	INIReader reader(tilemapPath.string());

	test.width = reader.GetInteger("header", "width", -1);
	test.height = reader.GetInteger("header", "height", -1);
	int tilesPerLayer = test.width * test.height;
	test.tileWidth = reader.GetInteger("header", "tilewidth", -1);
	test.tileHeight = reader.GetInteger("header", "tileheight", -1);
	test.tileset.initialize(reader.Get("tilesets", "tileset", "UNKNOWN"));
	test.tileset.columns = reader.GetInteger("tilesets", "columns", -1);
	test.initLayers(reader.Get("layer", "type", "UNKNOWN"), reader.Get("layer", "data", "UNKNOWN"), tilesPerLayer);

	return test;
}