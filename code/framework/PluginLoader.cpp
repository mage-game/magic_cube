#include "PluginLoader.h"
#include <memory>
#include "PluginProxy.h"
#include "Registry.h"
#include "Configer.h"

namespace MagicCube {

void PluginLoader::LoadPlugins() {
  auto id_card_vec = Configer::get_mutable_instance().GetPluginIDCards();
  for (const auto &id_card : id_card_vec) {
    LoadPlugin(id_card);
  }
}

void PluginLoader::UnLoadPlugins() {
  auto id_card_vec = Configer::get_mutable_instance().GetPluginIDCards();
  for (const auto &id_card : id_card_vec) {
    UnLoadPlugin(id_card);
  }
}

void PluginLoader::LoadPlugin(const IDCard &id_card) {
  auto plugin_proxy_ptr =
      Registry::get_mutable_instance().GetPlugin(id_card.name);
  if (plugin_proxy_ptr == nullptr) {
    plugin_proxy_ptr = std::make_shared<PluginProxy>(id_card);
    bool is_loaded = plugin_proxy_ptr->Load();
    if (is_loaded) {
      Registry::get_mutable_instance().RegisterPlugin(plugin_proxy_ptr);
    }
  }
}

void PluginLoader::UnLoadPlugin(const IDCard &id_card) {
  auto plugin_proxy_ptr =
      Registry::get_mutable_instance().GetPlugin(id_card.name);
  if (plugin_proxy_ptr) {
    Registry::get_mutable_instance().UnregisterPlugin(id_card.name);
    plugin_proxy_ptr->UnLoad();
  }
}

void PluginLoader::StartPlugins() {
  auto plugin_map = Registry::get_mutable_instance().GetAllPlugin();
  for (auto &it : plugin_map) {
    it.second->Start();
  }
}

void PluginLoader::StopPlugins() {
  auto plugin_map = Registry::get_mutable_instance().GetAllPlugin();
  for (auto &it : plugin_map) {
    it.second->Stop();
  }
}
}
