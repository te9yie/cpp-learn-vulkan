#pragma once
#include "t9/result.h"

namespace t9::sdl2 {

/// @brief SDL2 のコアシステム
class Core {
 private:
  // Drop.
  struct Drop {
    ~Drop();
  };

 private:
  std::unique_ptr<Drop> drop_;

 public:
  Core();

  /// @brief Core を構築する
  static Result<Core> make();
};

}  // namespace t9::sdl2