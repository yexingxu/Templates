#include "code/1-1tempaltes_function.hpp"

void Testmax() {
  std::cout << ::max(1, 3) << std::endl;       // 3
  std::cout << ::max(1, 3.1) << std::endl;     // 3
  std::cout << ::max(1.0, 3.14) << std::endl;  // 3.14
  std::string s1 = "mathematics";
  std::string s2 = "math";
  std::cout << ::max(s1, s2) << std::endl;  // mathematics
}

int main() {
  Testmax();

  return 0;
}