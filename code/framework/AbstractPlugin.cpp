#include "AbstractPlugin.h"

namespace MagicCube {

void AbstractPlugin::Start() {
  for (auto &it: module_ptr_map_) {
    std::shared_ptr<IModule> module_ptr = it.second;
    module_ptr->Awake();
    module_ptr->Initialize();
    module_ptr->AfterInit();
    module_ptr->CheckConfig();
    module_ptr->Start();
  }
}
void AbstractPlugin::Stop() {
  for (auto &it: module_ptr_map_) {
    std::shared_ptr<IModule> module_ptr = it.second;
    module_ptr->Stop();
    module_ptr->Finalize();
  }
}
void AbstractPlugin::AddModule(const std::shared_ptr<IModule> &module_ptr) {
  folly::fbstring name = module_ptr->GetName();
  if (!name.empty()) {
    module_ptr_map_[name] = module_ptr;
  }
}
void AbstractPlugin::RemoveModule(const folly::fbstring &name) {
  auto it = module_ptr_map_.find(name);
  if (it != module_ptr_map_.end()) {
    module_ptr_map_.erase(it);
  }
}
std::shared_ptr<IModule>
AbstractPlugin::GetModule(const folly::fbstring &name) {
  auto it = module_ptr_map_.find(name);
  if (it != module_ptr_map_.end()) {
    return it->second;
  }
  return nullptr;
}
}
