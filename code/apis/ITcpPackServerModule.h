#pragma once

#include <cstdint>
#include <vector>
#include <functional>
#include "folly/FBString.h"

using NET_RECEIVE_FUNCTOR = std::function<void(uint64_t conn_id,
                                               uint16_t msg_id,
                                               const char *msg,
                                               uint32_t len)>;

class ITcpPackServerModule {
 public:
  template<typename T>
  void AddReceiveCallBack(uint16_t msg_id, T *p_base, NET_RECEIVE_FUNCTOR cb_fun) {
    NET_RECEIVE_FUNCTOR functor = std::bind(cb_fun,
                                            p_base,
                                            std::placeholders::_1,
                                            std::placeholders::_2,
                                            std::placeholders::_3,
                                            std::placeholders::_4);
    //AddReceiveCallBack(msg_id, functor);
  }

  virtual bool SendMsg(uint16_t msg_id,
                       const folly::fbstring &msg,
                       uint64_t conn_id) = 0;
  virtual bool SendMsg(uint16_t msg_id,
                       const folly::fbstring &msg,
                       const std::vector<uint64_t> &conn_id_vec) = 0;
  virtual bool SendMsgToAll(uint16_t msg_id, const folly::fbstring &msg) = 0;
 protected:
  virtual void AddReceiveCallBack(uint16_t msg_id, NET_RECEIVE_FUNCTOR cb_fun) = 0;
  virtual void RemoveReceiveCallBack(uint16_t msg_id) = 0;
};
