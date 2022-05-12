#pragma once
#include "IModule.h"
#include "ITcpPackServerModule.h"

class TcpPackServerModule
    : public MagicCube::IModule, public ITcpPackServerModule {
 public:
  bool SendMsg(uint16_t msg_id,
               const folly::fbstring &msg,
               uint64_t conn_id) override;
  bool SendMsg(uint16_t msg_id,
               const folly::fbstring &msg,
               const std::vector<uint64_t> &conn_id_vec) override;
  bool SendMsgToAll(uint16_t msg_id, const folly::fbstring &msg) override;
 protected:
  void AddReceiveCallBack(uint16_t msg_id, NET_RECEIVE_FUNCTOR cb_fun) override;
  void RemoveReceiveCallBack(uint16_t msg_id) override;
};

