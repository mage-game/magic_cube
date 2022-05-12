#pragma once

#include <memory>
#include "boost/dll.hpp"
#include "folly/FBString.h"
#include "AbstractPlugin.h"

#define REGISTER_MODULE(base_class_name, class_name) \
    assert((std::is_base_of<IModule, class_name>::value)); \
    assert((std::is_base_of<base_class_name, class_name>::value));\
    auto module_ptr = std::make_shared<class_name>(); \
    module_ptr->SetName(#class_name); \
    AddModule(module_ptr)

#define UNREGISTER_MODULE(base_class_name, class_name)\
    assert((std::is_base_of<IModule, class_name>::value)); \
    assert((std::is_base_of<base_class_name, class_name>::value)); \
    RemoveModule(#class_name);

//#define MAGIC_CUBE_API extern "C" BOOST_SYMBOL_EXPORT
#define EXTERN_CREATE_PLUGIN_FUNC(class_name) \
public: \
static std::shared_ptr<AbstractPlugin> CreatePlugin() { \
  assert((std::is_base_of<AbstractPlugin, class_name>::value)); \
  auto plugin_ptr = std::make_shared<class_name>(); \
  return plugin_ptr; \
}

#define PLUGIN_DLL_ALIAS(class_name) \
BOOST_DLL_ALIAS(MagicCube::class_name::CreatePlugin, DLLCreatePlugin)

const folly::fbstring kDLLCreatePluginFuncName = "DLLCreatePlugin";
