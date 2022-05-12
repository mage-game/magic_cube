#include "PluginHelper.h"
#include "TcpPackServerModule.h"

namespace MagicCube {
class NetworkPlugin: public AbstractPlugin {
 EXTERN_CREATE_PLUGIN_FUNC(NetworkPlugin)
 public:
  bool Load() final {
    REGISTER_MODULE(ITcpPackServerModule, TcpPackServerModule);
    return true;
  }

  bool UnLoad() final {
    UNREGISTER_MODULE(ITcpPackServerModule, TcpPackServerModule);
    return true;
  }
};
PLUGIN_DLL_ALIAS(NetworkPlugin)
}
