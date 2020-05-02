#include <iostream>

// 参照は変数の別名をつくるもの
// int a = 10; int& ref = a
// ポインタとの違いはNULLを指し示せないこと

void twice (int& a) // 同じアドレスを指し示す変数aを新たに作る
{
  std::cout << a << std::endl;
  a *= 2;
  std::cout << a << std::endl;
}

void change_address (int& a)
{
  std::cout << a << std::endl;
  int tmp = 100;
  // &a = &tmp; // ポインタ変数ではないので指し示すアドレスを変えることはできない
  std::cout << a << std::endl;
}  

int main(int argc, char *argv[])
{
  int v = 16;
  std::cout << v << std::endl; // 16
  twice(v);                    // 16 32
  std::cout << v << std::endl; // 32

  return 0;
}

