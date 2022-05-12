#include "ITcpPackServerModule.h"
#include "PluginHelper.h"
#include "glog/logging.h"

#include <thread>
#include "libgo/coroutine.h"

using namespace std;
using namespace std::chrono;

const int nWork = 100;

// 大计算量的函数
int c = 0;
std::atomic<int> done{0};
void foo()
{
  int v = (int)rand();
  for (int i = 1; i < 20000000; ++i) {
    v *= i;
  }
  c += v;

  if (++done == nWork * 2)
    co_sched.Stop();
}

void f(){
  // 编写cpu密集型程序时, 可以延长协程执行的超时判断阈值, 避免频繁的worksteal产生
  co_opt.cycle_timeout_us = 1000 * 1000;

  // 普通的for循环做法
  auto start = system_clock::now();
  for (int i = 0; i < nWork; ++i)
    foo();
  auto end = system_clock::now();
  cout << "for-loop, cost ";
  cout << duration_cast<milliseconds>(end - start).count() << "ms" << endl;

  // 使用libgo做并行计算
  start = system_clock::now();
  for (int i = 0; i < nWork; ++i)
    go foo;

  // 创建8个线程去并行执行所有协程 (由worksteal算法自动做负载均衡)
  co_sched.Start(0);

  end = system_clock::now();
  cout << "go with coroutine, cost ";
  cout << duration_cast<milliseconds>(end - start).count() << "ms" << endl;
  cout << "result zero:" << c * 0 << endl;
}

int main(int argc, char *argv[]) {
  auto config_name = "MasterServer.xml";
  MagicCube::PluginHelper::Initialize(config_name);

  LOG(INFO) << "LOG(INFO)";
  LOG(WARNING) << "LOG(WARNING)";

  auto module_ptr = MagicCube::PluginHelper::GetModule<ITcpPackServerModule>();
  module_ptr->SendMsgToAll(0, "aaa");
  MagicCube::PluginHelper::Finalize();

//  f();

  return 0;
}