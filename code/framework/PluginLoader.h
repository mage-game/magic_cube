#pragma once

#include "boost/serialization/singleton.hpp"
#include "IDCardWrapper.h"

namespace MagicCube {
class PluginLoader: public boost::serialization::singleton<PluginLoader> {
 public:
  void LoadPlugins();
  void UnLoadPlugins();
  void LoadPlugin(const IDCard &id_card);
  void UnLoadPlugin(const IDCard &id_card);

  void StartPlugins();
  void StopPlugins();
};
}
