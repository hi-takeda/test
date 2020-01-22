#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

std::mutex mtx;

void worker() {
  // lock_guardよりいろいろ指定できて高機能
  //例えばtry_to_lockを指定すると、エラー報告やロックのリトライができる
  //ただし処理が重くなる(?)
  std::unique_lock<std::mutex> lock(mtx, std::try_to_lock);
  if (lock.owns_lock())
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
