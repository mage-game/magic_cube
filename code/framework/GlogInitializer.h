#pragma once

#include "boost/serialization/singleton.hpp"

namespace MagicCube {

class GlogInitializer: public boost::serialization::singleton<GlogInitializer> {
 public:
  void Initialize();
  void Finalize();
  void SetProperty();
};
}
