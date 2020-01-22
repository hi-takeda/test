#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

std::mutex mtx;

void worker() {
  // スコープの終わりでlock()変数が破棄される
  // unlock()を呼ぶ必要がなくて便利
  std::lock_guard<std::mutex> lock(mtx);
  std::cout << "thread id: " << std::this_thread::get_id() << std::endl;
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
