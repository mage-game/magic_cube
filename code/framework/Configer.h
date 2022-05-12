#pragma once

#include "boost/serialization/singleton.hpp"

#include "folly/FBString.h"
#include "folly/FBVector.h"

#include "IDCardWrapper.h"

namespace MagicCube {
struct GlogInfo {
  int32_t log_buf_secs;
  int32_t log_max_size;
  int32_t log_min_level;
  int32_t log_max_days;
  folly::fbstring log_file_prefix;
  GlogInfo() {
    log_buf_secs = 0;
    log_max_size = 100;
    log_min_level = 0;
    log_max_days = 3;
    log_file_prefix = "";
  }
  GlogInfo(const GlogInfo &obj) {
    *this = obj;
  }
  GlogInfo &operator=(const GlogInfo &obj) {
    log_buf_secs = obj.log_buf_secs;
    log_max_size = obj.log_max_size;
    log_min_level = obj.log_min_level;
    log_max_days = obj.log_max_days;
    log_file_prefix = obj.log_file_prefix;
    return *this;
  }
};
class Configer: public boost::serialization::singleton<Configer> {
 public:
  bool LoadConfig(const folly::fbstring &config_name);

  folly::fbvector<IDCard> GetPluginIDCards();
  GlogInfo GetGlogInfo();
 private:
  folly::fbvector<IDCard> plugin_info_vec_;
  GlogInfo glog_info_;
};
}