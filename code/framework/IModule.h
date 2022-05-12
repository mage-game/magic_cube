#pragma once

#include "folly/FBString.h"
#include "IAction.h"

namespace MagicCube {
class IModule: public IAction {
 public:
  ~IModule() override {}

  virtual void SetName(const folly::fbstring &name) { name_ = name; }
  virtual folly::fbstring GetName() { return name_; }
  void Awake() override {}
  void Initialize() override {}
  void AfterInit() override {}
  void CheckConfig() override {}
  void Start() override {}
  void Stop() override {}
  void Finalize() override {}
 private:
  folly::fbstring name_;
};
}
