//#include "ITcpPackServerModule.h"
//#include "PluginHelper.h"
//#include "glog/logging.h"

#include <folly/logging/xlog.h>
#include <folly/logging/LoggerDB.h>
#include <folly/logging/LogHandler.h>
#include <folly/logging/LogHandlerConfig.h>
#include <folly/logging/LogHandlerFactory.h>
#include <folly/logging/FileHandlerFactory.h>
#include <folly/logging/LogConfigParser.h>

#include <folly/init/Init.h>
#include <folly/logging/Init.h>
#include <folly/FBString.h>

//FOLLY_INIT_LOGGING_CONFIG("ERROR:x,folly=INFO:y;x=stream:stream=stdout;y=file:path=/tmp/y.log");

int main(int argc, char *argv[]) {
  folly::fbstring json_str = "{\n"
                             "  \"categories\": {\n"
                             "    \"\": { \"level\": \"INFO\", \"handlers\": [\"x\"] }\n"
                             "  },\n"
                             "  \"handlers\": {\n"
                             "    \"x\": {\n"
                             "      \"type\": \"file\",\n"
                             "      \"options\": {\n"
                             "        \"path\": \"/tmp/test.log\",\n"
                             "        \"async\": \"true\",\n"
                             "        \"sync_level\": \"INFO\",\n"
                             "        \"max_buffer_size\": \"1\"\n"
                             "      }\n"
                             "    }\n"
                             "  }\n"
                             "}";


  folly::LoggerDB::get().registerHandlerFactory(
      std::make_unique<folly::FileHandlerFactory>());

  folly::LogConfig log_config=folly::parseLogConfigJson(json_str);
  folly::LoggerDB::get().updateConfig(log_config);
  folly::LoggerDB::get().resetConfig(log_config);

  folly::Init init(&argc, &argv);

  XLOG(INFO, "now the normal log settings have been applied");
  XLOG(ERR, "now the normal log settings have been applied");


  return 0;
}