#include "SharedLibraryLoader.h"
#include "boost/exception/diagnostic_information.hpp"
#include "folly/Format.h"

namespace MagicCube {
SharedLibraryLoader::SharedLibraryLoader(const folly::fbstring &path) {
  shared_library_ptr_ = std::make_unique<boost::dll::shared_library>();
  shared_library_path_ = path;
}
bool SharedLibraryLoader::Load() {
  auto type = boost::dll::load_mode::load_with_altered_search_path
      | boost::dll::load_mode::append_decorations
      | boost::dll::load_mode::rtld_global;

  try {
    shared_library_ptr_->load(shared_library_path_.c_str(), type);
  } catch (const boost::exception &e) {
    folly::fbstring err_str = folly::sformat(
        "Load config failed. exception:{}",
        boost::diagnostic_information(e).c_str());
  }
  bool is_loaded = shared_library_ptr_->is_loaded();
  return is_loaded;
}
bool SharedLibraryLoader::UnLoad() {
  shared_library_ptr_->unload();
  bool is_loaded = shared_library_ptr_->is_loaded();
  return is_loaded;
}
}
