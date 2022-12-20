#pragma once
#include "t9/result.h"

namespace t9::vulkan {

/// @brief Vulkan インスタンス
class Instance {
 private:
  struct Drop {
    void operator()(VkInstance p) const;
  };

 private:
  std::unique_ptr<VkInstance_T, Drop> instance_;

 public:
  Instance(VkInstance instance);
};

/// @brief インスタンス構築
class InstanceBuilder {
 public:
  using Self = InstanceBuilder;

 private:
  VkInstanceCreateInfo info_{};

 public:
  InstanceBuilder();

  Self& extensions(const char* const* names, uint32_t count);

  Result<Instance> build();
};

}  // namespace t9::vulkan