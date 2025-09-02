#pragma once

//core
#include "Core/file.h"
#include "Core/Logger.h"
#include "Core/Factory.h"
#include "Core/Random.h"
#include "Core/Singleton.h"
#include "Core/Time.h"
#include "Core/StringHelperr.h"
#include "Core/Json.h"

// game
#include "Game/Actor.h"
#include "Game/Scene.h"
#include "Game/Game.h"
#include "Game/Object.h"

//physics
#include "Physics/Collidable.h"
#include "Physics/Physics.h"
#include "Physics/PhysicsBody.h"

//math
#include "Math/Math.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Math/Transform.h"
#include "Math/Rect.h"

//components
#include "Components/Animator.h"
#include "Game/Component.h"
#include "Components/RendererComponent.h"
#include "Components/SpriteRenderer.h"
#include "Components/RigidBody.h"
#include "Components/CircleCollider2d.h"

//events
#include "Event/Event.h"
#include "Event/Observer.h"
#include "Event/Event Manager.h"

//renderer
#include "Renderer/Text.h"
#include "Renderer/Texture.h"
#include "Renderer/TextureAnimation.h"

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