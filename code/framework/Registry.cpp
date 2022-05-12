#include "Registry.h"

namespace MagicCube {

bool Registry::RegisterPlugin(const std::shared_ptr<IPlugin> &plugin_ptr) {
  auto &lock_map = *sync_plugin_ptr_map_.wlock();
  folly::fbstring name = plugin_ptr->GetName();
  auto it = lock_map.find(name);
  if (it == lock_map.end()) {
    lock_map[name] = plugin_ptr;

    return true;
  }
  return false;
}

bool Registry::UnregisterPlugin(const folly::fbstring &name) {
  auto &lock_map = *sync_plugin_ptr_map_.wlock();
  auto it = lock_map.find(name);
  if (it != lock_map.end()) {
    lock_map.erase(it);

    return true;
  }
  return false;
}

std::shared_ptr<IPlugin>
Registry::GetPlugin(const folly::fbstring &name) const {
  auto lock_map = *sync_plugin_ptr_map_.rlock();
  auto it = lock_map.find(name);
  if (it != lock_map.end()) {
    return it->second;
  }
  return nullptr;
}

std::map<folly::fbstring, std::shared_ptr<IPlugin>>
Registry::GetAllPlugin() const {
  auto lock_map = *sync_plugin_ptr_map_.rlock();
  return lock_map;
}

}
