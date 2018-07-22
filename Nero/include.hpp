#pragma once

#define WIN32_LEAN_AND_MEAN  
#include <Windows.h>
#include <d3dx9.h>
#include <d3d9.h>
#pragma comment (lib, "d3d9")  
#pragma comment (lib, "d3dx9")  
#include <random>
#include <iostream>
#include <fstream>
#include <thread>
#include <filesystem>

#include "utils/netvar_manager.hpp"
#include "utils/static.hpp"
#include "utils/config.hpp"

#include "sdk/sdk.hpp"

#include "math/vector.hpp"

#include "overlay/render/Device3D9.hpp"
#include "menu/window.hpp"
#include "menu/menu.hpp"

#include "features/aim.hpp"
#include "features/visuals.hpp"
#include "features/misc.hpp"

