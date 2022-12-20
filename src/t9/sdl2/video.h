#pragma once
#include "t9/result.h"

namespace t9::sdl2 {

/// @brief SDL2 のビデオシステム
class Video {
 private:
  // Drop.
  struct Drop {
    ~Drop();
  };

 private:
  std::unique_ptr<Drop> drop_;

 public:
  Video();

  /// @brief Video を構築する
  static Result<Video> make();
};

}  // namespace t9::sdl2