#pragma once

enum ActionType {
  kAwake = 0,
  kInitialize,
  kAfterInit,
  kCheckConfig,
  kStart,
  kStop,
  kFinalize,
};

class IAction {
 public:
  virtual ~IAction() = default;

  virtual void Awake() = 0;
  virtual void Initialize() = 0;
  virtual void AfterInit() = 0;
  virtual void CheckConfig() = 0;
  virtual void Start() = 0;
  virtual void Stop() = 0;
  virtual void Finalize() = 0;
};
