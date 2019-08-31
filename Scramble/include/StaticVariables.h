#pragma once
#include <filesystem>
#include "getExePath.h"

const std::filesystem::path ASSETSDIR = std::filesystem::path(getExePath()) / L"data";