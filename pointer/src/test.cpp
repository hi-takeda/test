#include <iostream>

void func (int& a)
{
  a = 0;
  std::cout << &a << std::endl;
}

int main(int argc, char *argv[])
{
  int var = 10;
  int* ptr = &var;
  int& ref = *ptr;
  int notref = *ptr;

  std::cout << &var << std::endl; // 同じアドレス
  std::cout << ptr << std::endl;  // 同じアドレス
  std::cout << &ref << std::endl; // 同じアドレス
  std::cout << &notref << std::endl; // これだけ違うアドレス（コピーが起きた）
  
  return 0;
}
