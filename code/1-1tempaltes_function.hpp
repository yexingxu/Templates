#include <iostream>
#include <string>

template <typename T>
T max(T a, T b) {
  return b < a ? a : b;
}

// 模板被编译两次，分别发生在实例化前和实例化期间
// 实例化前检查模板代码本身，包括
// 检查语法是否正确，如是否遗漏分号
// 发现使用不依赖于模板参数的 unknown name（类型名、函数名......）
// 检查不依赖于模板参数的 static assertion
// 实例化期间，再次检查模板代码保证所有代码有效（如某个类型不支持
// operator<），特别的是，会再次检查依赖于模板参数的部分
// template <typename T>
// void f(T x) {
//   undeclared();   // first-phase compile-time error if undeclared() unknown
//   undeclared(x);  // second-phase compile-time error if undeclared(T) unknown
//   static_assert(sizeof(int) > 10,
//                 "int too small");  // always fails if sizeof(int) <= 10
//   static_assert(sizeof(T) > 10,
//                 "T too small");  // fails if instantiated for T with size <=
//                 10
// }

//实参的推断不允许自动类型转换，要求每个 T 都要正确匹配。传值调用参数时，cv
//限定符会被忽略，引用转换为对应的值类型，数组或函数转换为指针

// int a = 1;
// const int b = 42;
// int& c = a;
// int arr[4];
// std::string s;
// ::max(a, b);        // OK：T 推断为 int
// ::max(b, b);        // OK：T 推断为 int
// ::max(a, c);        // OK：T 推断为 int
// ::max(&a, arr);     // OK：T 推断为 int*
// ::max(1, 3.14);     // 错误：T 推断为 int 和 double
// ::max("hello", s);  // 错误：T 推断为 const char[6] 和 std::string

// * 两个参数类型不同时，有三个解决方案
//   * 强制转换参数类型：`max(static_cast<double>(1), 3.14)`
//   * 指定 T：`max<double>(1, 3.14)`
//   * 用两个模板参数指定不同类型
// * 类型推断对默认实参无效，在圆括号的参数列表中指定T的默认实参是无效的

// template <typename T>
// void f(T = "");

// f(1);  // OK：T 推断为 int，调用 f<int>(1)
// f();   // 错误：不能推断 T

// template <typename T, typename U>
// auto max(T a, U b) {
//   return b < a ? a : b;
// }

template <typename T, typename U>
auto max(T a, U b) -> decltype(b < a ? a : b) {
  return b < a ? a : b;
}