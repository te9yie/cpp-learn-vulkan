#pragma once
#include <cassert>
#include <optional>

namespace t9 {

/// @brief Result 用無効値.
constexpr inline std::nullopt_t none = std::nullopt;

/// @brief 戻り値を少し便利に扱うクラス
template <typename T>
class Result {
 private:
  std::optional<T> value_;

 public:
  Result() = default;
  Result(std::nullopt_t) : value_(std::nullopt) {}
  Result(T value) : value_(std::move(value)) {}

  /// @brief bool への明示的な型変換
  explicit operator bool() const { return value_.has_value(); }

  /// @brief 正常値の取り出し (Move)
  T unwrap() {
    assert(value_);
    return std::move(value_.value());
  }
};

}  // namespace t9