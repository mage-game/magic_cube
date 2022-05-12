#pragma once

#include <memory>
#include <cstdint>

#include "folly/FBString.h"
#include "Registry.h"
#include "Configer.h"
#include "GlogInitializer.h"
#include "PluginLoader.h"
#include "AbstractPlugin.h"
#include "PluginDefine.h"

namespace MagicCube {
class PluginHelper {
 public:
  static void Initialize(const folly::fbstring &config_name){
    bool is_loaded = Configer::get_mutable_instance().LoadConfig(config_name);
    if (is_loaded) {
      GlogInitializer::get_mutable_instance().Initialize();
      GlogInitializer::get_mutable_instance().SetProperty();
      PluginLoader::get_mutable_instance().LoadPlugins();
      PluginLoader::get_mutable_instance().StartPlugins();
    }
  }
  static void Finalize(){
    PluginLoader::get_mutable_instance().StopPlugins();
    PluginLoader::get_mutable_instance().UnLoadPlugins();
    GlogInitializer::get_mutable_instance().Finalize();
  }
  static std::shared_ptr<IPlugin> GetPlugin(const folly::fbstring &dll_name) {
    return Registry::get_mutable_instance().GetPlugin(dll_name);
  }

  template<typename T>
  static std::shared_ptr<T> GetModule() {
    std::shared_ptr<T> t_ptr = nullptr;
    auto plugin_ptr_map = Registry::get_mutable_instance().GetAllPlugin();
    for (const auto &pair : plugin_ptr_map) {
      folly::fbstring info_name = typeid(T).name();
      uint32_t pos = info_name.find_first_of('I') + 1;
      folly::fbstring class_name = info_name.substr(pos, info_name.length());
      auto i_ptr = pair.second->GetModule(class_name);
      if (i_ptr) {
        t_ptr = std::dynamic_pointer_cast<T>(i_ptr);
        break;
      }
    }
    return t_ptr;
  }
};
}
