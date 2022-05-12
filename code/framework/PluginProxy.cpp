#include "PluginProxy.h"
#include "PluginDefine.h"

namespace MagicCube {
PluginProxy::PluginProxy(const IDCard &id_card) {
  SetIDCard(id_card);
  shared_library_loader_ptr_ = std::make_unique<SharedLibraryLoader>(id_card.name);
  plugin_ptr_.reset();
}

bool PluginProxy::Load() {
  bool is_loaded = shared_library_loader_ptr_->Load();
  if (is_loaded) {
    auto create_plugin_func = shared_library_loader_ptr_->
        GetSymbol<std::shared_ptr<AbstractPlugin>()>(kDLLCreatePluginFuncName);
    plugin_ptr_ = create_plugin_func();
    if (plugin_ptr_) {
      bool is_successful = plugin_ptr_->Load();
      if (is_successful) {
        plugin_ptr_->SetIDCard(GetIDCard());
      }
    }
  }
  return is_loaded;
}

bool PluginProxy::UnLoad() {
  if (plugin_ptr_) {
    plugin_ptr_->UnLoad();
    plugin_ptr_.reset();
  }
  return shared_library_loader_ptr_->UnLoad();
}

void PluginProxy::Start() {
  if (plugin_ptr_) {
    plugin_ptr_->Start();
  }
}

void PluginProxy::Stop() {
  if (plugin_ptr_) {
    plugin_ptr_->Stop();
  }
}

void PluginProxy::AddModule(const std::shared_ptr<IModule> &module_ptr) {
  if (plugin_ptr_) {
    plugin_ptr_->AddModule(module_ptr);
  }
}

void PluginProxy::RemoveModule(const folly::fbstring &name) {
  if (plugin_ptr_) {
    plugin_ptr_->RemoveModule(name);
  }
}

std::shared_ptr<IModule> PluginProxy::GetModule(const folly::fbstring &name) {
  if (plugin_ptr_) {
    return plugin_ptr_->GetModule(name);
  }
  return nullptr;
}

}
