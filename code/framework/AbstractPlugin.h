#pragma once

#include <memory>
#include <map>
#include "folly/FBString.h"

#include "IPlugin.h"
#include "IModule.h"

namespace MagicCube {
class AbstractPlugin: public IPlugin {
 public:
  ~AbstractPlugin() override = default;
  bool Load() override = 0;
  bool UnLoad() override = 0;

  void Start() final;
  void Stop() final;
  void AddModule(const std::shared_ptr<IModule> &module_ptr) final;
  void RemoveModule(const folly::fbstring &name) final;
  std::shared_ptr<IModule> GetModule(const folly::fbstring &name) final;

 private:
  std::map<folly::fbstring, std::shared_ptr<IModule>> module_ptr_map_;
};

}
