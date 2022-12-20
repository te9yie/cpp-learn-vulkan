#include "instance.h"

namespace t9::vulkan {

// Instance::Drop.
void Instance::Drop::operator()(VkInstance p) const {
  vkDestroyInstance(p, nullptr);
}

Instance::Instance(VkInstance instance) : instance_(instance) {}

// InstanceBuilder.
InstanceBuilder::InstanceBuilder() {
  info_.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
}

InstanceBuilder::Self& InstanceBuilder::extensions(const char* const* names,
                                                   uint32_t count) {
  info_.enabledExtensionCount = count;
  info_.ppEnabledExtensionNames = names;
  return *this;
}

Result<Instance> InstanceBuilder::build() {
  VkInstance instance = VK_NULL_HANDLE;
  auto err = vkCreateInstance(&info_, nullptr, &instance);
  if (err != VK_SUCCESS) return none;
  return Instance(instance);
}

}  // namespace t9::vulkan