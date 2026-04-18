# hpcalc
🔥 单文件纯 C++ 高精度大整数库 | 有符号整数 | 运算符重载 | Karatsuba 乘法

**hpcalc.h内部提供详细中文使用说明**

**detailed instructions provided inside hpcalc.h**

![GitHub Stars](https://img.shields.io/github/stars/rylTianChen/cpp_hpcalc_high-precision?style=social)
![GitHub Forks](https://img.shields.io/github/forks/rylTianChen/cpp_hpcalc_high-precision?style=social)
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
#include<iostream>
#include"hpcalc.h"
using namespace grnum;
HP a, b, c;
char op;
int main(){
	while(1){
		std::cin >> a >> op >> b;
		c.clear();
		if(op == '+') c = a+b;
		if(op == '-') c = a-b;
		if(op == '*') c = a*b;
		if(op == '/') c = a/b;
		if(op == '^') c = HP_pow(a, b);
		if(op == '%') c = a%b;
		if(c.isEMPTY()) puts("Error");
		else putsHP(c);
	}
	return 0;
}
```
## 编译命令
```bat
g++ test.cpp -O2 -std=c++14 -o test.exe
```

## 性能测试

| 测试项目 | Python 内置 | hpcalc (C++) |
|---------|------------|--------------|
| 2^200000 计算 | ___ ms | ___ ms |
| 10 万位 + 10 万位 加法 | ___ ms | ___ ms |
| 10 万位 × 10 万位 乘法 | ___ ms | ___ ms |
| 100 万位 加法 | ___ ms | ___ ms |
| 大数取模（100 万位） | ___ ms | ___ ms |

## 📌 支持运算
**数学运算**
* 加减乘除模：+ - * / %
* 乘方：HP_pow(a, b)
* 复合赋值：+= -= *= /= %=
+ 自增 / 自减：++ --

**位运算**
* 与：a & b
* 或：a | b
* 异或：a ^ b
* 取反：~a
* 基于 1024 进制补码实现

**比较运算**
`> < >= <= == != `全支持，可与 int/long long 混用

## 🧩 常用 API
```cpp
HP x = 123456;
x.length();      // 获取位数
x.sign();        // 获取符号：1 / -1 / 0
x.isEMPTY();     // 是否为错误值
x.clear();       // 清空为 EMPTY
x.reverse();     // 数字反转
x.isPalindrome();// 是否回文数
x.AppendZero(5); // 末尾加 5 个 0
x.RemoveTail(3); // 删除末尾 3 位
x.GetDigit(2);   // 获取倒数第 2 位
```

## ⚠️ 注意事项
1. 仅支持有符号大整数，不支持浮点数
2. 负数取模规则：余数与被除数同号
3. 指数超过 8 位时，HP_pow 返回 EMPTY
4. 错误 / 空值参与运算 → 返回 EMPTY
5. 最大长度限制：1e8 位

## 📧 作者
天辰

lyrTianChen09@outlook.com

## 📄 许可证
开源免费，可自由使用、修改、分发
