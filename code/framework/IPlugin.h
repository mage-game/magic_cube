#pragma once

#include <memory>
#include "folly/FBString.h"
#include "IModule.h"
#include "IDCardWrapper.h"

namespace MagicCube {
struct IPlugin: public IDCardWrapper {
  ~IPlugin() override = default;
  virtual bool Load() = 0;
  virtual bool UnLoad() = 0;
  virtual void Start() {}
  virtual void Stop() {}
  virtual void AddModule(const std::shared_ptr<IModule> &module_ptr) {}
  virtual void RemoveModule(const folly::fbstring &name) {}
  virtual std::shared_ptr<IModule>
  GetModule(const folly::fbstring &name) { return nullptr; }
};
}
