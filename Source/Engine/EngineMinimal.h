#pragma once

//core
#include "Core/file.h"
#include "Core/Logger.h"
#include "Core/Random.h"
#include "Core/Singleton.h"
#include "Core/Time.h"
#include "Core/StringHelperr.h"

// game
#include "Game/Actor.h"
#include "Game/Scene.h"
#include "Game/Game.h"
#include "Game/Object.h"

//math
#include "Math/Math.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Math/Transform.h"

//components
#include "Game/Component.h"
#include "Components/RendererComponent.h"
#include "Components/SpriteRenderer.h"

//resources
#include "Resources/Resource.h"
#include "Resources/ResourceManager.h"

//third-party library
#include <fmod.hpp>
#include <fmod_errors.h>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3/SDL_ttf.h>

//standard library
#include <iostream>
#include <memory>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <list>
#include <cstdlib>
#include <algorithm>
#include <random>
#include <cmath>
#include <filesystem>