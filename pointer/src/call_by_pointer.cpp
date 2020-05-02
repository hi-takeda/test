#include <iostream>

// ポインタ変数はアドレスを格納するもの
// ex) int *ptr; ptr = &var

// 関数は引数の型の示す値のコピーをつくって内部で利用する

// ポインタ渡しの関数＝ポインタ変数（アドレス）のコピーをつくる
// ポインタ渡しの関数では渡されたアドレスを使って
// その指し示す値を書き換え可能だが，ポインタ自体
// を書き換えることはできない

void twice (int* a) // int*型の値のコピーをaに格納して内部で利用
{
  std::cout << *a << " : in twice(int*)" << std::endl;
  *a *= 2;
  std::cout << *a << " : in twice(int*)" << std::endl;
}

void address_change (int* a) // int*型の値のコピーをaに格納して内部で利用
{
  std::cout << *a << " : in address_change(int*)" << std::endl;
  int tmp = 100;
  a = &tmp;
  std::cout << *a << " : in address_change(int*)" << std::endl;
}

int main(int argc, char *argv[])
{
  int v = 16;
  std::cout << v << " : in main()" << std::endl; // 16
  twice(&v);                                     // 16 32
  std::cout << v << " : in main()" << std::endl; // 32
  address_change(&v);                            // 32 100
  std::cout << v << " : in main()" << std::endl; // 32

  std::cout << std::endl;
  
  int* w;
  *w = 16;
  std::cout << *w << " : in main()" << std::endl; // 16
  twice(w);                                       // 16 32
  std::cout << *w << " : in main()" << std::endl; // 32
  address_change(w);                              // 32 100
  std::cout << *w << " : in main()" << std::endl; // 32

  return 0;
}
