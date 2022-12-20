#include "t9/sdl2/prelude.h"

int main(int /*argc*/, char* /*argv*/[]) {
#if defined(_MSC_VER)
  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

  SDL_LogSetAllPriority(SDL_LOG_PRIORITY_VERBOSE);

  using namespace t9::sdl2;
  auto core = Core::make().unwrap();
  auto video = Video::make().unwrap();
  auto window = WindowBuilder("Learn Vulkan", 16 * 60, 9 * 60).build().unwrap();

  bool loop = true;
  while (loop) {
    if (window.handle_event() == HandleEventResult::Quit) {
      loop = false;
    }
  }

  return 0;
}