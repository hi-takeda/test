#include <iostream>

void twice (int a)
{
  std::cout << a << " : in twice(int a)" << std::endl;
  a *= 2;
  std::cout << a << " : in twice(int a)" << std::endl;
}

int main(int argc, char *argv[])
{
  int v = 16;
  std::cout << v << " : in main()" << std::endl;
  twice(v);
  std::cout << v << " : in main()" << std::endl;
  return 0;
}
