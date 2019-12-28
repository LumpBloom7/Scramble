#pragma once
#include <iostream>
#include <filesystem>
#include <unordered_map>
#include <sstream>
#include "stdIncludes.h"
#define INI_MAX_LINE 9999
#include "INIReader.h"
#include "Game.h"
#include "StaticVariables.h"


struct Tileset {
	void initialize(std::string initData) {
		for (char& c : initData)
			if (c == ',') c = ' ';

		std::stringstream ss(initData);
		std::filesystem::path tmpPath;
		ss >> tmpPath >> tileWidth >> tileHeight >> xOffset >> yOffset;
		path = ASSETSDIR / "Assets" / tmpPath;
	}
	std::filesystem::path path;
	int tileWidth, tileHeight;
	int xOffset, yOffset;
	int columns;
};

struct Layer {
	std::string name;
	Tileset tileset;

	std::vector<int> layerData;
	int layerWidth, layerHeight;
};

struct Tilemap {
	void initLayers(std::string layerNames, std::string layerData, int totalTiles) {
		for (char& c : layerData)
			if (c == ',') c = ' ';

		std::stringstream ssName(layerNames);
		std::stringstream ssData(layerData);
		std::string nameBuffer;
		while (std::getline(ssName, nameBuffer)) {
			Layer newLayer;
			newLayer.name = nameBuffer;
			newLayer.layerData = std::vector<int>(totalTiles);
			std::string dataBuffer;
			std::getline(ssData, dataBuffer);
			std::stringstream ssTmp(dataBuffer);

			for (int i = 0; i < totalTiles; ++i) {
				ssTmp >> newLayer.layerData[i];
				--newLayer.layerData[i];
			}
			newLayer.tileset = tileset;
			newLayer.layerWidth = width * tileWidth;
			newLayer.layerHeight = height * tileHeight;

			layers.emplace_back(newLayer);
		}

	}
	int width, height;
	int tileWidth, tileHeight;
	Tileset tileset;

	std::vector<Layer> layers;
};

Tilemap generateTilemap(std::filesystem::path tilemapPath);