#include "Configer.h"
#include <filesystem>
#include <iostream>
#include "folly/Format.h"
#include "boost/property_tree/ptree.hpp"
#include "boost/exception/diagnostic_information.hpp"
#include "boost/property_tree/xml_parser.hpp"
#include "glog/logging.h"

namespace MagicCube {
const folly::fbstring kConfigFolder =
    folly::sformat("{}/../config/", std::filesystem::current_path().c_str());

bool Configer::LoadConfig(const folly::fbstring &config_name) {
  folly::fbstring xml_path = kConfigFolder + config_name;
  bool is_dir_exist = std::filesystem::exists(xml_path.toStdString());
  if (!is_dir_exist) {
    return false;
  }
  try {
    boost::property_tree::ptree pt;
    boost::property_tree::xml_parser::read_xml(xml_path.toStdString(), pt);
    auto log_info_tree = pt.get_child("server.log");
    for (const auto &node : log_info_tree) {
      auto &log_info = node.second;
      glog_info_.log_buf_secs =
          log_info.get<int32_t>("log_buf_secs", 0);
      glog_info_.log_max_size =
          log_info.get<int32_t>("log_max_size", 100);
      glog_info_.log_max_days =
          log_info.get<int32_t>("log_max_days", 7);
      glog_info_.log_min_level =
          log_info.get<int32_t>("log_min_level", google::INFO);
      glog_info_.log_file_prefix =
          log_info.get<folly::fbstring>("log_file_prefix", "");
    }

    auto plugin_info_tree = pt.get_child("server.plugins");
    for (const auto &node : plugin_info_tree) {
      if (node.first == "plugin") {
        auto &plugin_info = node.second;
        IDCard id_card;
        id_card.name = plugin_info.get<folly::fbstring>("<xmlattr>.name", "");
        id_card.version =
            plugin_info.get<folly::fbstring>("<xmlattr>.version", "");
        id_card.description =
            plugin_info.get<folly::fbstring>("<xmlattr>.description", "");
        plugin_info_vec_.push_back(id_card);
      }
    }
  } catch (const boost::exception &e) {
    folly::fbstring err_str = folly::sformat(
        "Load plugin config failed. exception:{}",
        boost::diagnostic_information(e).c_str());
    std::cout << err_str << std::endl;
  }
  return true;
}

folly::fbvector<IDCard> Configer::GetPluginIDCards() {
  return plugin_info_vec_;
}

GlogInfo Configer::GetGlogInfo() {
  return glog_info_;
}

}
