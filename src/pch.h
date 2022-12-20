#pragma once
#if defined(_MSC_VER)
#include <crtdbg.h>
#endif

#include <SDL.h>
#include <SDL_vulkan.h>
#include <vulkan/vulkan.h>

#include <cassert>
#include <functional>
#include <memory>
#include <string>

#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_vulkan.h"