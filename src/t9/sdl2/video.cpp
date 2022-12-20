#include "video.h"

namespace t9::sdl2 {

// Video::Drop.
Video::Drop::~Drop() {
  SDL_LogInfo(SDL_LOG_CATEGORY_VIDEO, "shutdown SDL video.");
  SDL_QuitSubSystem(SDL_INIT_VIDEO);
}

// Video.
Video::Video() : drop_(std::make_unique<Drop>()) {}

/*static*/ Result<Video> Video::make() {
  SDL_LogInfo(SDL_LOG_CATEGORY_VIDEO, "initialize SDL video.");
  if (SDL_InitSubSystem(SDL_INIT_VIDEO) < 0) {
    SDL_LogCritical(SDL_LOG_CATEGORY_VIDEO, "SDL_InitSubSystem: %s",
                    SDL_GetError());
    return none;
  }
  return Video();
}

}  // namespace t9::sdl2