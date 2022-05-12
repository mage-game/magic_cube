#include "GlogInitializer.h"

#include <filesystem>
#include "folly/Format.h"
#include "folly/FBString.h"
#include "glog/logging.h"
#include "Configer.h"

namespace MagicCube {

const folly::fbstring kLogFolder =
    folly::sformat("{}/../logs/", std::filesystem::current_path().c_str());

static void SignalHandle(const char *data, int32_t size) {
  // can send message to email or phone
  LOG(ERROR) << folly::fbstring(data, size);
}

void GlogInitializer::Initialize() {
  GlogInfo glog_info = Configer::get_mutable_instance().GetGlogInfo();

  google::InitGoogleLogging("");
  // higher than ERROR logs will to output to the screen at the same time
  google::SetStderrLogging(google::GLOG_FATAL);
  folly::fbstring log_file_path = folly::sformat(
      "{}{}-", kLogFolder, glog_info.log_file_prefix);
  // set higher than INFO log file path and filename prefix
  google::SetLogDestination(google::GLOG_INFO, log_file_path.c_str());
  // set screen log color
  FLAGS_colorlogtostderr = true;
  // logs just output on screen?
  FLAGS_logtostderr = false;
  // logs also output on screen?
  FLAGS_alsologtostderr = true;
  // stop log file if disk full
  FLAGS_stop_logging_if_full_disk = true;
  // log prefix will show in every log line
  FLAGS_log_prefix = true;
  // log buffer seconds(default: 30s)
  FLAGS_logbufsecs = glog_info.log_buf_secs;
  // max log size per one file
  FLAGS_max_log_size = glog_info.log_max_size;
  FLAGS_minloglevel = glog_info.log_min_level;

  // set log file extension
  google::SetLogFilenameExtension(".log");
  // catch core dumped
  google::InstallFailureSignalHandler();
  // if SIGSEGV then call SignalHandle
  google::InstallFailureWriter(SignalHandle);

  google::EnableLogCleaner(glog_info.log_max_days);
}

void GlogInitializer::Finalize() {
  // Shutdown google's logging library.
  google::ShutdownGoogleLogging();
}

void GlogInitializer::SetProperty() {
  GlogInfo glog_info = Configer::get_mutable_instance().GetGlogInfo();

  // higher than ERROR logs will to output to the screen at the same time
  google::SetStderrLogging(google::GLOG_FATAL);
  folly::fbstring log_file_path = folly::sformat(
      "{}{}-", kLogFolder, glog_info.log_file_prefix);
  // set higher than INFO log file path and filename prefix
  google::SetLogDestination(google::GLOG_INFO, log_file_path.c_str());
  // set screen log color
  FLAGS_colorlogtostderr = true;
  // logs just output on screen?
  FLAGS_logtostderr = false;
  // logs also output on screen?
  FLAGS_alsologtostderr = true;
  // stop log file if disk full
  FLAGS_stop_logging_if_full_disk = true;
  // log prefix will show in every log line
  FLAGS_log_prefix = true;
  // log buffer seconds(default: 30s)
  FLAGS_logbufsecs = glog_info.log_buf_secs;
  // max log size per one file
  FLAGS_max_log_size = glog_info.log_max_size;
  FLAGS_minloglevel = glog_info.log_min_level;

  // set log file extension
  google::SetLogFilenameExtension(".log");
  // catch core dumped
  google::InstallFailureSignalHandler();
  // if SIGSEGV then call SignalHandle
  google::InstallFailureWriter(SignalHandle);

  google::EnableLogCleaner(glog_info.log_max_days);
}

}
