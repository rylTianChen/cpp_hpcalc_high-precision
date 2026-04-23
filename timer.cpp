#include<iostream>
#include<chrono>
#include<string>
typedef std::string string;
#include"hpcalc.h"
using namespace grnum;
int main() {
    int digits = 1e7;
    string s1(digits, '3');
    string s2(digits, '8');

    HP a = s1;
    HP b = s2;
    HP c;

    puts("预热中...");
        c = a + b;
//        c = a - b;
//        c = a * b;
//        c = a / b;

    puts("开始测试");
    const int TEST_COUNT = 5;
    long long times[TEST_COUNT];

    for(int t = 0; t < TEST_COUNT; t++) {
        auto st = std::chrono::steady_clock::now();
        // 被测运算
        c = a%998244353;
        // C = A - B;
        // C = A * B;
        // C = A / B;
        auto ed = std::chrono::steady_clock::now();
        times[t] = std::chrono::duration_cast<std::chrono::milliseconds>(ed - st).count();
        std::cout << "第" << t+1 << "次: " << times[t] << " ms" << std::endl;
    }

    // 计算平均
    long long sum = 0;
    for(int t = 0; t < TEST_COUNT; t++) sum += times[t];
    std::cout << "\n平均: " << sum / TEST_COUNT << " ms" << std::endl;

    return 0;
}
