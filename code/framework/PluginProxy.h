#pragma once

#include <memory>

#include "boost/dll.hpp"
#include "folly/FBString.h"

#include "AbstractPlugin.h"
#include "SharedLibraryLoader.h"

namespace MagicCube {
class PluginProxy: public IPlugin {
 public:
  explicit PluginProxy(const IDCard &id_card);
  bool Load() final;
  bool UnLoad() final;
  void Start() final;
  void Stop() final;
  void AddModule(const std::shared_ptr<IModule> &module_ptr) final;
  void RemoveModule(const folly::fbstring &name) final;
  std::shared_ptr<IModule> GetModule(const folly::fbstring &name) final;

 private:
  std::unique_ptr<SharedLibraryLoader> shared_library_loader_ptr_;
  std::shared_ptr<AbstractPlugin> plugin_ptr_;
};

}
