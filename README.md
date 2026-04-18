# hpcalc
🔥 单文件纯 C++ 高精度大整数库 | 有符号整数 | 运算符重载 | Karatsuba 乘法

![GitHub Stars](https://img.shields.io/github/stars/rylTianChen/hpcalc?style=social)
![GitHub Forks](https://img.shields.io/github/forks/rylTianChen/hpcalc?style=social)
![C++14](https://img.shields.io/badge/Language-C%2B%2B14-blue)
![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux-lightgray)
![Single File](https://img.shields.io/badge/Single%20File-%E2%9C%94-brightgreen)
![Karatsuba](https://img.shields.io/badge/Karatsuba-Multiplication-orange)
![License](https://img.shields.io/badge/License-MIT-green)

## ✨ 项目简介
hpcalc 是**纯手写、单文件、无任何依赖**的高精度有符号整数计算库，适用于算法竞赛、大数运算、教学与工程项目。
仅需引入 `hpcalc.h` 即可使用，支持完整运算符重载与位运算。

## 🎯 核心特性
- ✅ **单文件开箱即用**：仅 `hpcalc.h`，无需编译、无需链接
- ✅ **无第三方依赖**：不依赖 GMP、Boost 等任何库
- ✅ **千进制存储**：速度优于传统十进制
- ✅ **Karatsuba 分治乘法**：大数乘法性能大幅提升
- ✅ **完整运算符重载**：`+ - * / %` 直接使用
- ✅ **支持位运算**：`& | ^ ~`（补码实现）
- ✅ **错误安全**：异常场景统一返回 `EMPTY`
- ✅ **丰富工具函数**：反转、回文、末尾补 0、删位、取指定位等

## 🚀 快速示例
```cpp
#include <iostream>
#include "hpcalc.h"
using namespace grnum;

int main() {
    HP a = 2;
    HP b = 200000;
    HP c = HP_pow(a, b);

    std::cout << "位数：" << c.length() << std::endl;
    std::cout << c << std::endl;
    return 0;
}
