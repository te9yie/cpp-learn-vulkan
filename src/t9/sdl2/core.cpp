#include "core.h"

namespace t9::sdl2 {

// Core::Drop.
Core::Drop::~Drop() {
  SDL_LogInfo(SDL_LOG_CATEGORY_SYSTEM, "shutdown SDL.");
  SDL_Quit();
}

// Core.
Core::Core() : drop_(std::make_unique<Drop>()) {}

/*static*/ Result<Core> Core::make() {
  SDL_LogInfo(SDL_LOG_CATEGORY_SYSTEM, "initialize SDL.");
  if (SDL_Init(0) < 0) {
    SDL_LogCritical(SDL_LOG_CATEGORY_SYSTEM, "SDL_Init: %s", SDL_GetError());
    return none;
  }
  return Core();
}

}  // namespace t9::sdl2