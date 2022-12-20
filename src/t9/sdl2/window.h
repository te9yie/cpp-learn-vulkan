#pragma once
#include "t9/result.h"

namespace t9::sdl2 {

/// @brief handle_event() の戻り値
enum class HandleEventResult {
  Continue,  ///< 継続
  Quit,      ///< 停止
};

/// @brief HandleEvent フック関数
using HandleEventFunc = std::function<void(const SDL_Event&)>;

/// @brief ウィンドウ
class Window {
 private:
  struct Drop {
    void operator()(SDL_Window* w) const;
  };

 private:
  std::unique_ptr<SDL_Window, Drop> window_;

 public:
  explicit Window(SDL_Window* w);

  /// @brief ウィンドウイベントの処理
  HandleEventResult handle_event();

  /// @brief ウィンドウイベントの処理(フック関数指定)
  HandleEventResult handle_event(const HandleEventFunc& f);

  /// @brief SDL_Window* への変換
  SDL_Window* into() const { return window_.get(); }
};

/// @brief ウィンドウ構築
class WindowBuilder {
 public:
  using Self = WindowBuilder;

 private:
  std::string title_;
  int x_ = SDL_WINDOWPOS_UNDEFINED;
  int y_ = SDL_WINDOWPOS_UNDEFINED;
  int width_ = 0;
  int height_ = 0;
  Uint32 flags_ = 0;

 public:
  /// @brief ウィンドウ必須情報の設定
  WindowBuilder(std::string_view title, int w, int h);

  // clang-format off
  Self& title(std::string_view value) { title_ = value; return *this; }
  Self& x(int value) { x_ = value; return *this; }
  Self& y(int value) { y_ = value; return *this; }
  Self& width(int value) { width_ = value; return *this; }
  Self& height(int value) { height_ = value; return *this; }
  Self& flags(Uint32 value) { flags_ = value; return *this; }
  // clang-format on

  /// @brief ウィンドウの構築
  Result<Window> build();
};

}  // namespace t9::sdl2