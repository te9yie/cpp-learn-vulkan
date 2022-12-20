#include "t9/sdl2/prelude.h"
#include "t9/vulkan/prelude.h"

int main(int /*argc*/, char* /*argv*/[]) {
#if defined(_MSC_VER)
  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

  SDL_LogSetAllPriority(SDL_LOG_PRIORITY_VERBOSE);

  using namespace t9::sdl2;
  auto core = Core::make().unwrap();
  auto video = Video::make().unwrap();
  auto window = WindowBuilder("Learn Vulkan", 16 * 60, 9 * 60)
                    .flags(SDL_WINDOW_VULKAN)
                    .build()
                    .unwrap();

  uint32_t ext_count = 0;
  SDL_Vulkan_GetInstanceExtensions(window.into(), &ext_count, nullptr);
  std::vector<const char*> extensions(ext_count);
  SDL_Vulkan_GetInstanceExtensions(window.into(), &ext_count,
                                   extensions.data());

  auto vk = t9::vulkan::InstanceBuilder()
                .extensions(extensions.data(), ext_count)
                .build()
                .unwrap();

  bool loop = true;
  while (loop) {
    if (window.handle_event() == HandleEventResult::Quit) {
      loop = false;
    }
  }

  return 0;
}