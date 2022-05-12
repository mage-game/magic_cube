#include "TcpPackServerModule.h"

#include <iostream>

bool TcpPackServerModule::SendMsg(uint16_t msg_id,
                                  const folly::fbstring &msg,
                                  uint64_t conn_id) {
  return false;
}
bool TcpPackServerModule::SendMsg(uint16_t msg_id,
                                  const folly::fbstring &msg,
                                  const std::vector<uint64_t> &conn_id_vec) {
  return false;
}
bool
TcpPackServerModule::SendMsgToAll(uint16_t msg_id, const folly::fbstring &msg) {
  std::cout << "TcpPackServerModule::SendMsg" << std::endl;
  return false;
}
void TcpPackServerModule::AddReceiveCallBack(uint16_t msg_id,
                                             NET_RECEIVE_FUNCTOR cb_fun) {

}
void TcpPackServerModule::RemoveReceiveCallBack(uint16_t msg_id) {

}
