#include "window.h"

namespace t9::sdl2 {

// Window::Drop.
void Window::Drop::operator()(SDL_Window* w) const {
  SDL_LogInfo(SDL_LOG_CATEGORY_VIDEO, "destroy window.");
  SDL_DestroyWindow(w);
}

// Window.
/*explicit*/ Window::Window(SDL_Window* w) : window_(w) {}

HandleEventResult Window::handle_event() { return handle_event(nullptr); }

HandleEventResult Window::handle_event(const HandleEventFunc& f) {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (f) {
      f(e);
    }
    if (e.type == SDL_QUIT) {
      return HandleEventResult::Quit;
    }
    if (e.type == SDL_WINDOWEVENT && e.window.event == SDL_WINDOWEVENT_CLOSE &&
        e.window.windowID == SDL_GetWindowID(into())) {
      return HandleEventResult::Quit;
    }
  }
  return HandleEventResult::Continue;
}

// WindowBuilder.
WindowBuilder::WindowBuilder(std::string_view title, int w, int h)
    : title_(title), width_(w), height_(h) {}

Result<Window> WindowBuilder::build() {
  SDL_LogInfo(SDL_LOG_CATEGORY_VIDEO, "create window.");
  auto w = SDL_CreateWindow(title_.c_str(), x_, y_, width_, height_, flags_);
  if (!w) {
    SDL_LogCritical(SDL_LOG_CATEGORY_VIDEO, "SDL_CreateWindow: %s",
                    SDL_GetError());
    return none;
  }
  return Window(w);
}

}  // namespace t9::sdl2