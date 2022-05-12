#pragma once

#include <memory>
#include "boost/dll.hpp"
#include "folly/FBString.h"

namespace MagicCube {
class SharedLibraryLoader {
 public:
  explicit SharedLibraryLoader(const folly::fbstring &path);
  bool Load();
  bool UnLoad();

  template<typename T>
  T &GetSymbol(const folly::fbstring &func_name) {
    return shared_library_ptr_->get_alias<T>(func_name.c_str());
  }
 private:
  std::unique_ptr<boost::dll::shared_library> shared_library_ptr_;
  folly::fbstring shared_library_path_;
};
}
