#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

std::mutex mtx;

void worker() {
  // lock()とunlock()で囲むと資源専有するので出力が乱れない
  mtx.lock();
  std::cout << "thread id: " << std::this_thread::get_id() << std::endl;
  mtx.unlock();
}

int main() {
  // スレッドを4つ作る
  std::vector<std::thread> ths(4);
  for (auto& th : ths)
    th = std::thread(worker);

  // すべてのスレッドが終わるのを待つ
  for (auto& th : ths)
    th.join();

  return 0;
}
