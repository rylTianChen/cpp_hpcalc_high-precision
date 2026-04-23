import time
import sys

def test_python_int():
    # 准备数据
    digits = 10000000  # 和C++保持一致
    s1 = '7' * digits
    s2 = '5' * digits
    print("准备构造")
    sys.set_int_max_str_digits(1000000000)
    A = int(s1)
    B = int(s2)
    
    # 预热
    print("预热中...")
    C = A + B
    # C = A - B
    # C = A * B
    # C = A // B  # Python整数除法
    
    # 正式测试
    TEST_COUNT = 5
    times = []
    
    for t in range(TEST_COUNT):
        start = time.perf_counter()
        
        # 被测运算（和C++保持一致）
        C = A%998244353
        # C = A - B
        # C = A * B
        # C = A // B
        
        end = time.perf_counter()
        ms = (end - start) * 1000
        times.append(ms)
        print(f"第{t+1}次: {ms:.2f} ms")
    
    print(f"\n平均: {sum(times)/TEST_COUNT:.2f} ms")

if __name__ == "__main__":
    test_python_int()