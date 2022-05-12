#pragma once

#include <map>
#include <memory>

#include "folly/FBString.h"
#include "folly/Synchronized.h"
#include "boost/serialization/singleton.hpp"

#include "IPlugin.h"

namespace MagicCube {
class Registry: public boost::serialization::singleton<Registry> {
 public:
  bool RegisterPlugin(const std::shared_ptr<IPlugin> &plugin_ptr);
  bool UnregisterPlugin(const folly::fbstring &name);
  std::shared_ptr<IPlugin> GetPlugin(const folly::fbstring &name) const;
  std::map<folly::fbstring, std::shared_ptr<IPlugin>> GetAllPlugin() const;

 private:
  folly::Synchronized<std::map<folly::fbstring, std::shared_ptr<IPlugin>>>
      sync_plugin_ptr_map_;
};
}