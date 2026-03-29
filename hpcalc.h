﻿/*
欢迎使用此高精度库!
作者:天辰、豆包
版本:1.0
使用说明:
	这是一个有符号整数高精度计算库,不支持浮点数运算。
	变量类型名称为HP。例: HP a=2;可以定义一个名为a的高精度变量,它存储的整数为2。
	可以直接使用数学运算符、逻辑运算符进行运算。例: HP a = b+2-3;
	本库中包含乘方HP_pow()。例: HP_pow(a, b)会返回a的b次方。
    输入:
        使用std::cin进行输入。
	    或者使用getint()输入一个高精度整数。例: a = getint();
	    getint()会先过滤不可见字符,然后开始输入,遇到非数字字符时结束输入。
	    如果出现输入错误,高精度变量的值是EMPTY。
    输出:
    	使用std::cout进行输出。
    	或者使用putint()输出一个高精度数。例: putint(a);
    错误返回值:
	    若出现已知错误,返回值都是EMPTY,即空值。
	    使用isEMPTY()获得一个HP变量是否是空值。例: if(a.isEMPTY())
    注意:
	    1. 将HP转换为int或ll时,若HP值超过int或ll范围,返回值是0。
	    2. 乘方运算限制：当指数的位数超过16位时,判定结果过大,HP_pow()返回EMPTY。
	    3. 零值与空值区分
		   EMPTY特征为EMPTY[0] = 0（错误/无效值）,
		   ZERO特征为ZERO[0] = 1（合法数值0）。
	    4. 自增(++)、自减(--)运算符基于加号/减号重载实现,若操作空值(EMPTY),结果仍为空值。
	    5. 负数取模规则：余数与被除数同号（例：(-7)%3=-1、7%(-3)=1）。
	    6. 本库采用千进制存储（JW=1000）,运算时自动压缩/解压十进制数,对外无感知。
    祝您使用愉快!
    若发现问题,请向lyrTianChen09@outlook.com反馈。
天辰还开发了一个高精度计算器。获取方式：
	链接: https://pan.baidu.com/s/1X_E5OkSiDlJ-IigefdfurA
	提取码: b2ef
*/
/*
Welcome to use this high-precision library!
Author: TianChen / Doubao
Version: 1.0
Instructions:
	This is a signed integer high-precision calculation library,
	and it does not support floating-point operations.
	The type name is HP. e.g.: HP a = 2;
	This defines a high-precision variable named a that stores the integer value 2.
	You can directly use mathematical and logical operators for calculations.
	e.g.: HP a = b+2-3;
	This library includes the power function HP_pow().
	e.g.: HP_pow(a, b) will return the value of a to the power of b.
	Input:
		You can use std::cin to read a high-precision integer.
		Or you can use getint() to read a high-precision integer. e.g.: a = getint();
		getint() will first filter non-visible characters and then begin reading input,
		and end input when encountering non-numeric character.
		If an input error occurs, value of the HP variable will be EMPTY.
	Output: Use std::cout to output.
			Or use putint() to print a HP. e.g.: putint(a);
	Error return value:
		If a known error occurs, the return value is EMPTY, which represents an empty value.
		Use isEMPTY() to check whether an HP variable is empty.
		e.g.: if(a.isEMPTY())
	Caution:
		1. When converting HP to int or ll, if HP value exceeds the range of int or ll,
		   the return value is 0.
		2. Power operation limit: If the number of digits of the exponent exceeds 16,
		   the result is judged to be too large, and HP_pow() returns EMPTY.
		3. Distinction between zero and empty values:
		   EMPTY features EMPTY[0] = 0 (error/invalid value),
		   while ZERO features ZERO[0] = 1 (valid value 0).
		4. Increment (++) and decrement (--) operators are implemented based on
		   overloaded plus/minus operators. If operating on an empty value (EMPTY),
		   the result remains empty.
		5. Negative number modulo rule:
		   The remainder has the same sign as the dividend (e.g.: (-7)%3=-1, 7%(-3)=1).
		6. This library uses thousand-based storage (JW=1000),
		   automatically compresses/decompresses decimal numbers during operations,
		   and is transparent to the user.
	We wish you a pleasant experience!
	If there are any problems, please give feedback to lyrTianChen09@outlook.com.
TianChen has also developed a high-precision calculator. To obtain it:
	https://pan.baidu.com/s/1X_E5OkSiDlJ-IigefdfurA
	Extract Code: b2ef
*/

#ifndef GRNUM_DEF_H
#define GRNUM_DEF_H 1031149997108990

#include<vector>
#include<iostream>

namespace grnum{
	typedef std::vector<int> vi;
	typedef long long ll;
	const char fh[] = "*/^%";//运算符 operator
	const int JW = 1000;//千进制 Thousand-based storage system
	vi EMPTY(1, 0);
	//空,Error时返回值 EMPTY, the return value on error
	//EMPTY特征: EMPTY[0] = 0    Feature of EMPTY: EMPTY[0] = 0
	vi ONE(2, 0), M_ONE(2, 0), ZERO(2, 0);//1 -1 0
	char FirstInit = 1;//第一次执行构造函数时初始化全局变量
	//Initialize global variables on first constructor execution
	const int MAX_INT = 2147483647, MIN_INT = -2147483648;
	const ll MAX_LL =  9223372036854775807ll, MIN_LL = -9223372036854775808ll;

	//数相关函数 functions about numbers
	int max(int x, int y) {return x>y ? x : y;}
	int min(int x, int y) {return x<y ? x : y;}
	int abs(int x) {return x>0 ? x : -x;}
	void swap(int &x, int &y) {int t = x; x = y, y = t;}
	int IntToOne(int x) {return x>0 ? 1 : -1;}

	//字符相关函数 functions about characters
	char PosiNega(char x) {return x=='+' ? '-' : '+';}
	char SymMulti(char x, char y) {return x==y ? '+' : '-';}
	char IsDigit(char t) {return t>='0' && t<='9';}// 是数字
	char IsZF(char t) {return t=='+' || t=='-';}// 是正负号
	char IsFh(char x){//是运算符
	    for(auto ch : fh)
	        if(ch && ch==x) return 1;
	    return 0;
	}

	//数和符号转换函数 functions about converting of numbers and characters
	char IntToZF(int x) {return x>=0 ? '+' : '-';}
	char ZFToInt(char x) {return x=='+' ? 1 : -1;}
	char llToZF(ll x) {return x>=0 ? '+' : '-';}

	//vector相关函数 functions about vector
	char HP_IsZERO(vi &a) {return a[0]==1 && !a[1];}//是0 Checks if the value is 0
	char HP_IsONE(vi &a) {return a[0]==1 && a[1]==1;}//是1 Checks if the value is 1
	char HP_IsM_ONE(vi &a) {return a[0]==-1 && a[1]==1;}//是-1 Checks if the value is -1
	void VecSwap(vi &a, vi &b) {a.swap(b);}
	void AllResize(int n, vi &a, vi &b, vi &c){
		a.resize(n), b.resize(n), c.resize(n);
	}//运算之前统一长度防止指针越界
	//Unify lengths before operations to prevent index out of bounds
	void HP_PopFrontZero(vi &a){
        int n = abs(a[0]);
        int f = a[0] > 0 ? 1 : -1;
        while(n>1 && a[n]==0) n--, a.pop_back();
        a[0] = n*f;
	}//去除前导零 Remove leading zeros
	short HP_VecCmp(vi a, vi b){
        int na=abs(a[0]), nb=abs(b[0]), i;
        if(na != nb) return na>nb ? 1 : -1;
        for(i=na; i>0; i--)
            if(a[i] != b[i]) return a[i]>b[i] ? 1 : -1;
        return 0;
	}//无符号整数比较大小 Compare unsigned integers
	void HP_reverse(vi &a){
	    int n = abs(a[0]), i;
	    for(i=1; i+i<=n; i++)
	        swap(a[i], a[n-i+1]);
	}//倒序存储 Reverse the vector storage
	vi HP_zip(vi a){//十进制压为千进制 Compress decimal to thousand-based
	    int f = a[0]>0 ? 1 : -1, n = abs(a[0]), i;
	    a.resize(n+5, 0);
	    int nb = (n+2)/3;
	    vi b(nb+5, 0);
	    for(i=1; i<=n; i+=3) b[i/3+1] = a[i+2]*100+a[i+1]*10+a[i];
	    b[0] = f*nb;
	    HP_PopFrontZero(b);
	    return b;
	}
	vi HP_unzip(vi a){//千进制解压为十进制 Decompress thousand-based to decimal
	    int f = a[0]>0 ? 1 : -1, n = abs(a[0]), i;
	    a.resize(n+5, 0);
	    int nb = (n<<1)+n;//n*3
	    vi b(nb+5, 0);
	    for(i=1; i<=n; i++){
	        b[i*3-3+1] = a[i]%10;
	        b[i*3-3+2] = a[i]/10%10;
	        b[i*3-3+3] = a[i]/100;
	    }
	    b[0] = f*nb;
	    HP_PopFrontZero(b);
	    return b;
	}
	ll HP_VecToll(vi &b){//高精度转为ll    Convert high-precision to long long
	    b = HP_unzip(b);
	    ll ans = 0; int nb = abs(b[0]);
	    while(nb) ans = ans*10+b[nb--];
	    return ans;
	}//使用时保证不溢出
	//Ensure no overflow when using this function


	//高精度计算函数声明
	//Declarations of high-precision calculation functions
	vi HP_Plus(vi a, vi b);
	vi HP_Minus(vi a, vi b);
	vi HP_Multiply(vi a, vi b);
	vi HP_Karatsuba(int n, vi a, vi b);
	vi HP_SimMul(vi a, vi b);
	char HP_DivCmp(int r, int n, vi &a, vi &b);
	vi HP_Divide(vi a, vi b);
	vi HP_Power(vi a, ll b);
	vi HP_Module(vi a, vi b);
	
	class HP{
		private:
			vi num;//高精度数,千进制 high-precision number, thousand-based

		public:
    		void clear() {num.clear(), num.push_back(0);}//清空 clear
    		bool isEMPTY() {return this->num[0] == 0;}
			//是否为错误值 Checks if it is the empty (error) value

    		/*
            变量命名规则:
            	以变量x为例。
            	若名称形如x,说明x是一个vi
            	若名称形如xi,说明xi是一个int或ll
            	若名称形如xbi,说明xbi是一个HP
			*/
			/*
			Variable naming rules:
				Take variable x as an example:
				If named x, it is a vi;
				if xi, it is an int or ll;
				if xbi, it is an HP.
   			*/
			//构造函数 Constructors
			HP(){
				num.clear(); num.push_back(0);
				if(FirstInit){
					FirstInit = 0;
					ONE[1] = ONE[0] = 1;
					M_ONE[0] = -1, M_ONE[1] = 1;
					ZERO[0] = 1;
				}
			}
			HP(int xi){
				if(!xi){
					num.push_back(1);
					num.push_back(0);
					return;
				}
				char z = IntToZF(xi);
				xi = abs(xi);
				vi temp(1, 0);
				while(xi){
					temp.push_back(xi%10);
					xi /= 10;
				}
				int len = temp.size()-1;
				temp[0] = ZFToInt(z)*len;
				num = HP_zip(temp);
				if(FirstInit){
					FirstInit = 0;
					ONE[1] = ONE[0] = 1;
					M_ONE[0] = -1, M_ONE[1] = 1;
					ZERO[0] = 1;
				}
			}
			HP(ll xi){
				if(!xi){
					num.push_back(1);
					num.push_back(0);
					return;
				}
				char z = llToZF(xi);
				xi = xi>0 ? xi : -xi;
				vi temp(1, 0);
				while(xi){
					temp.push_back(xi%10);
					xi /= 10;
				}
				int len = temp.size()-1;
				temp[0] = ZFToInt(z)*len;
				num = HP_zip(temp);
				if(FirstInit){
					FirstInit = 0;
					ONE[1] = ONE[0] = 1;
					M_ONE[0] = -1, M_ONE[1] = 1;
					ZERO[0] = 1;
				}
			}
			HP(vi &v){
				num = v;
				if(FirstInit){
					FirstInit = 0;
					ONE[1] = ONE[0] = 1;
					M_ONE[0] = -1, M_ONE[1] = 1;
					ZERO[0] = 1;
				}
			}

			
			//重载运算符 Overloaded operator
			HP operator + (const HP &bbi) const {
				//高精度 + 高精度    high-precision + high-precision
				vi a = this->num, b = bbi.num;
				if(!a[0] || !b[0]) return HP(EMPTY);
				vi c = HP_Plus(a, b);
				return HP(c);
			}
			HP operator + (const int bi) const {
				//高精度 + int    high-precision + int
				return *this + HP(bi);
			}
			HP operator + (const ll bi) const {
				//高精度 + ll    high-precision + ll
				return *this + HP(bi);
			}
			friend HP operator + (const int ai, const HP &bbi){
				//int + 高精度    int + high-precision
				return HP(ai) + bbi;
			}
			friend HP operator + (const ll ai, const HP &bbi){
				//ll + 高精度    ll + high-precision
				return HP(ai) + bbi;
			}

			HP operator - (const HP &bbi) const {
				//高精度 - 高精度    high-precision - high-precision
				vi a = this->num, b = bbi.num;
				if(!a[0] || !b[0]) return HP(EMPTY);
				vi c = HP_Minus(a, b);
				return HP(c);
			}
			HP operator - (const int bi) const {
				//高精度 - int    high-precision - int
				return *this - HP(bi);
			}
			HP operator - (const ll bi) const {
				//高精度 - ll    high-precision - ll
				return *this - HP(bi);
			}
			friend HP operator - (const int ai, const HP &bbi){
				//int - 高精度    int - high-precision
				return HP(ai) - bbi;
			}
			friend HP operator - (const ll ai, const HP &bbi){
				//ll - 高精度    ll - high-precision
				return HP(ai) - bbi;
			}
			friend HP operator - (const HP &bbi){
				//-高精度(相反数)    Unary minus for high-precision (opposite number)
				vi b = bbi.num;
				b[0] = -b[0];
				return HP(b);
			}

			HP operator * (const HP &bbi) const {
				//高精度 * 高精度    high-precision * high-precision
				vi a = this->num, b = bbi.num;
				if(!a[0] || !b[0]) return HP(EMPTY);
				vi c = HP_Multiply(a, b);
				return HP(c);
			}
			HP operator * (const int bi) const {
				//高精度 * int    high-precision * int
				return *this * HP(bi);
			}
			HP operator * (const ll bi) const {
				//高精度 * ll    high-precision * ll
				return *this * HP(bi);
			}
			friend HP operator * (const int ai, const HP &bbi){
				//int * 高精度    int * high-precision
				return HP(ai) * bbi;
			}
			friend HP operator * (const ll ai, const HP &bbi){
				//ll * 高精度    ll * high-precision
				return HP(ai) * bbi;
			}

			HP operator / (const HP &bbi) const {
				//高精度 / 高精度    high-precision / high-precision
				vi a = this->num, b = bbi.num;
				if(!a[0] || !b[0]) return HP(EMPTY);
				if(HP_IsZERO(b)) return HP(EMPTY);
				//除以0,错误 Division by zero, Error
				else{
					vi c = HP_Divide(a, b);
					return HP(c);
				}
			}
			HP operator / (const int bi) const {
				//高精度 / int    high-precision / int
				return *this / HP(bi);
			}
			HP operator / (const ll bi) const {
				//高精度 / ll    high-precision / ll
				return *this / HP(bi);
			}
			friend HP operator / (const int ai, const HP &bbi){
				//int / 高精度    int / high-precision
				return HP(ai) / bbi;
			}
			friend HP operator / (const ll ai, const HP &bbi){
				//ll / 高精度    ll / high-precision
				return HP(ai) / bbi;
			}

			HP operator % (const HP &bbi) const {
				//高精度 % 高精度    high-precision % high-precision
				vi a = this->num, b = bbi.num;
				if(!a[0] || !b[0]) return HP(EMPTY);
				if(HP_IsZERO(b)) return HP(EMPTY);
				//模0,错误 Module by zero, Error
				else{
					vi c = HP_Module(a, b);
					return HP(c);
				}
			}
			HP operator % (const int bi) const {
				//高精度 % int    high-precision % int
				return *this % HP(bi);
			}
			HP operator % (const ll bi) const {
				//高精度 % ll    high-precision % ll
				return *this % HP(bi);
			}
			friend HP operator % (const int ai, const HP &bbi){
				//int % 高精度    int % high-precision
				return HP(ai) % bbi;
			}
			friend HP operator % (const ll ai, const HP &bbi){
				//ll % 高精度    ll % high-precision
				return HP(ai) % bbi;
			}

			bool operator > (const HP &bbi) const {
				//高精度 > 高精度    high-precision > high-precision
				vi a = this->num, b = bbi.num;
				if(!a[0] || !b[0]) return false;
				int na = a[0], nb = b[0];
				//异号 different signs
				if(na>0 && nb<0) return true;
				if(na<0 && nb>0) return false;
				//同号 the same sign
				int f = IntToOne(na), i;
				na = abs(na), nb = abs(nb);
				if(na > nb) return f>0 ? true : false;
				if(na < nb) return f>0 ? false : true;
				for(i=na; i; i--){
					if(a[i] > b[i]) return f>0 ? true : false;
					if(a[i] < b[i]) return f>0 ? false : true;
				}
				return false;//相等 equal
			}
			bool operator > (const int bi) const {
				//高精度 > int    high-precision > int
				return *this > HP(bi);
			}
			bool operator > (const ll bi) const {
				//高精度 > ll    high-precision > ll
				return *this > HP(bi);
			}
			friend bool operator > (const int ai, const HP &bbi){
				//int > 高精度    int > high-precision
				return HP(ai) > bbi;
			}
			friend bool operator > (const ll ai, const HP &bbi){
				//ll > 高精度    ll > high-precision
				return HP(ai) > bbi;
			}

			bool operator >= (const HP &bbi) const {
				//高精度 >= 高精度    high-precision >= high-precision
				vi a = this->num, b = bbi.num;
				if(!a[0] || !b[0]) return false;
				int na = a[0], nb = b[0];
				if(na>0 && nb<0) return true;
				if(na<0 && nb>0) return false;
				int f = IntToOne(na), i;
				na = abs(na), nb = abs(nb);
				if(na > nb) return f>0 ? true : false;
				if(na < nb) return f>0 ? false : true;
				for(i=na; i; i--){
					if(a[i] > b[i]) return f>0 ? true : false;
					if(a[i] < b[i]) return f>0 ? false : true;
				}
				return true;//相等 equal
			}
			bool operator >= (const int bi) const {
				//高精度 >= int    high-precision >= int
				return *this >= HP(bi);
			}
			bool operator >= (const ll bi) const {
				//高精度 >= ll    high-precision >= ll
				return *this >= HP(bi);
			}
			friend bool operator >= (const int ai, const HP &bbi){
				//int >= 高精度    int >= high-precision
				return HP(ai) >= bbi;
			}
			friend bool operator >= (const ll ai, const HP &bbi){
				//ll >= 高精度    ll >= high-precision
				return HP(ai) >= bbi;
			}

			bool operator < (const HP &bbi) const {
				//高精度 < 高精度    high-precision < high-precision
				vi a = this->num, b = bbi.num;
				if(!a[0] || !b[0]) return false;
				int na = a[0], nb = b[0];
				if(na>0 && nb<0) return false;
				if(na<0 && nb>0) return true;
				int f = IntToOne(na), i;
				na = abs(na), nb = abs(nb);
				if(na > nb) return f>0 ? false : true;
				if(na < nb) return f>0 ? true : false;
				for(i=na; i; i--){
					if(a[i] > b[i]) return f>0 ? false : true;
					if(a[i] < b[i]) return f>0 ? true : false;
				}
				return false;//相等 equal
			}
			bool operator < (const int bi) const {
				//高精度 < int    high-precision < int
				return *this < HP(bi);
			}
			bool operator < (const ll bi) const {
				//高精度 < ll    high-precision < ll
				return *this < HP(bi);
			}
			friend bool operator < (const int ai, const HP &bbi){
				//int < 高精度    int < high-precision
				return HP(ai) < bbi;
			}
			friend bool operator < (const ll ai, const HP &bbi){
				//ll < 高精度    ll < high-precision
				return HP(ai) < bbi;
			}

			bool operator <= (const HP &bbi) const {
				//高精度 <= 高精度    high-precision <= high-precision
				vi a = this->num, b = bbi.num;
				if(!a[0] || !b[0]) return false;
				int na = a[0], nb = b[0];
				if(na>0 && nb<0) return false;
				if(na<0 && nb>0) return true;
				int f = IntToOne(na), i;
				na = abs(na), nb = abs(nb);
				if(na > nb) return f>0 ? false : true;
				if(na < nb) return f>0 ? true : false;
				for(i=na; i; i--){
					if(a[i] > b[i]) return f>0 ? false : true;
					if(a[i] < b[i]) return f>0 ? true : false;
				}
				return true;//相等 equal
			}
			bool operator <= (const int bi) const {
				//高精度 <= int    high-precision <= int
				return *this <= HP(bi);
			}
			bool operator <= (const ll bi) const {
				//高精度 <= ll    high-precision <= ll
				return *this <= HP(bi);
			}
			friend bool operator <= (const int ai, const HP &bbi){
				//int <= 高精度    int <= high-precision
				return HP(ai) <= bbi;
			}
			friend bool operator <= (const ll ai, const HP &bbi){
				//ll <= 高精度    ll <= high-precision
				return HP(ai) <= bbi;
			}

			bool operator == (const HP &bbi) const {
				//高精度 == 高精度    high-precision == high-precision
				vi a = this->num, b = bbi.num;
				if(!a[0] || !b[0]) return false;
				if(a[0] != b[0]) return false;
				int n = abs(a[0]), i;
				for(i=n; i; i--){
					if(a[i] != b[i]) return false;
				}
				return true;
			}
			bool operator == (const int bi) const {
				//高精度 == int    high-precision == int
				return *this == HP(bi);
			}
			bool operator == (const ll bi) const {
				//高精度 == ll    high-precision == ll
				return *this == HP(bi);
			}
			friend bool operator == (const int ai, const HP &bbi){
				//int == 高精度    int == high-precision
				return HP(ai) == bbi;
			}
			friend bool operator == (const ll ai, const HP &bbi){
				//ll == 高精度    ll == high-precision
				return HP(ai) == bbi;
			}

			bool operator != (const HP &bbi) const {
				//高精度 != 高精度    high-precision != high-precision
				vi a = this->num, b = bbi.num;
				if(!a[0] || !b[0]) return false;
				if(a[0] != b[0]) return true;
				int n=abs(a[0]), i;
				for(i=n; i; i--){
					if(a[i] != b[i]) return true;
				}
				return false;
			}
			bool operator != (const int bi) const {
				//高精度 != int    high-precision != int
				return *this != HP(bi);
			}
			bool operator != (const ll bi) const {
				//高精度 != ll    high-precision != ll
				return *this != HP(bi);
			}
			friend bool operator != (const int ai, const HP &bbi){
				//int != 高精度    int != high-precision
				return HP(ai) != bbi;
			}
			friend bool operator != (const ll ai, const HP &bbi){
				//ll != 高精度    ll != high-precision
				return HP(ai) != bbi;
			}

			operator int() const {
				//int = 高精度    Cast to int from high-precision
				if(*this>MAX_INT || *this<MIN_INT) return 0;
				vi b = HP_unzip(this->num);
				if(!b[0]) return 0;
				int ai = 0, na = abs(b[0]), f = IntToOne(b[0]), i;
				for(i=na; i; i--) ai = ai*10+b[i];
				ai = ai*f;
				return ai;
			}
			operator ll() const {
				//ll = 高精度    Cast to long long from high-precision
				if(*this>MAX_LL || *this<MIN_LL) return 0;
				vi b = HP_unzip(this->num);
				if(!b[0]) return 0;
				ll ai = 0, na = abs(b[0]), f = IntToOne(b[0]), i;
				for(i=na; i; i--) ai = ai*10+b[i];
				ai = ai*f;
				return ai;
			}
			
			HP operator += (const HP &bbi){
				//高精度 += 高精度    high-precision += high-precision
				*this = *this + bbi;
				return *this;
			}
			HP operator += (const int bi){
				//高精度 += int    high-precision += int
				*this = *this + HP(bi);
				return *this;
			}
			HP operator += (const ll bi){
				//高精度 += ll    high-precision += ll
				*this = *this + HP(bi);
				return *this;
			}

			HP operator -= (const HP &bbi){
				//高精度 -= 高精度    high-precision -= high-precision
				*this = *this - bbi;
				return *this;
			}
			HP operator -= (const int bi){
				//高精度 -= int    high-precision -= int
				*this = *this - HP(bi);
				return *this;
			}
			HP operator -= (const ll bi){
				//高精度 -= ll    high-precision -= ll
				*this = *this - HP(bi);
				return *this;
			}

			HP operator *= (const HP &bbi){
				//高精度 *= 高精度    high-precision *= high-precision
				*this = *this * bbi;
				return *this;
			}
			HP operator *= (const int bi){
				//高精度 *= int    high-precision *= int
				*this = *this * HP(bi);
				return *this;
			}
			HP operator *= (const ll bi){
				//高精度 *= ll    high-precision *= ll
				*this = *this * HP(bi);
				return *this;
			}

			HP operator /= (const HP &bbi){
				//高精度 /= 高精度    high-precision /= high-precision
				*this = *this / bbi;
				return *this;
			}
			HP operator /= (const int bi){
				//高精度 /= int    high-precision /= int
				*this = *this / HP(bi);
				return *this;
			}
			HP operator /= (const ll bi){
				//高精度 /= ll    high-precision /= ll
				*this = *this / HP(bi);
				return *this;
			}

			HP operator %= (const HP &bbi){
				//高精度 %= 高精度    high-precision %= high-precision
				*this = *this % bbi;
				return *this;
			}
			HP operator %= (const int bi){
				//高精度 %= int    high-precision %= int
				*this = *this % HP(bi);
				return *this;
			}
			HP operator %= (const ll bi){
				//高精度 %= ll    high-precision %= ll
				*this = *this % HP(bi);
				return *this;
			}

			HP operator ++ (){
				//++高精度    ++high-precision
				*this = *this + HP(1);
				return *this;
			}
			HP operator ++ (int flag){
				//高精度++    high-precision++
				HP temp = *this;
				*this = *this + HP(1);
				return temp;
			}

			HP operator -- (){
				//--高精度    --high-precision
				*this = *this - HP(1);
				return *this;
			}
			HP operator -- (int flag){
				//高精度--    high-precision--
				HP temp = *this;
				*this = *this - HP(1);
				return temp;
			}

			//输入重载运算符 Overloaded input operator
			friend std::istream& operator>> (std::istream &is, HP &cbi){
				vi a(1, 0);//空值,初始值 EMPTY, the original value
				int na = 0;//数长度 length of the number
				char za = 0;//符号 sign(+/-)
				char t;//临时字符 temporary character
				while(is.get(t)){
					if(t<=32 && na) break;
					// 读完之后不可见字符 invisible characters after reading in
					if(t == '\n'){//遇到换行符(ASCII < 20) line break (ASCII < 20)
						if(na) break;
						//已经有数字,输入结束 there have been digits, input ends
						else continue;//还没有数字,继续输入
						//there haven't been digits, continue to input
					}
					if(!is) break;// 输入结束 end of input
					if(IsZF(t)){// 是正负号   the character is a sign
						if(na) break;// 已经开始输入数字了 have started to read in digits
						else if(za) break;// 已经有符号了 have a symbol already
						else za = t;
					}else if(IsFh(t)) break;// 是其他运算符 other calculation characters
					else if(IsDigit(t)){
						a.push_back(t-48);
						na++;
					}//读入数字 read in digits
					else break;//其他字符 other characters
				}
				if(!za) za = '+';
				a[0] = na*ZFToInt(za);
				if(!a[0]) cbi.num = EMPTY;
				else{
					HP_reverse(a);
					cbi.num = HP_zip(a);
				}
				return is;
			}
			//输出重载运算符 Overloaded output operator
			friend std::ostream& operator<< (std::ostream &os, const HP cbi){
				vi c = HP_unzip(cbi.num);
				if(!c[0]) return os;
				int nc = abs(c[0]);
				os << (c[0]<0 ? "-" : "");
				for(; nc; nc--) os << c[nc];
				return os;
			}

			//乘方 power
			friend HP HP_pow(HP abi, HP bbi){
				vi a = abi.num, b = bbi.num;
				if(!a[0] || !b[0]) return HP(EMPTY);
				if(b[0] < 0) return HP(EMPTY);//负次幂 negative exponent
				if(HP_IsZERO(a) && HP_IsZERO(b)) return HP(EMPTY);//0^0无意义 0^0 is undefined
				if(HP_IsZERO(b)) return HP(ONE);//a^0 = 1 (a!=0)
				if(HP_IsZERO(a)) return HP(ZERO);//0^b = 0 (b!=0)
				if(HP_IsONE(a)) return HP(ONE);//1^a = 1
				if(HP_IsM_ONE(a)) return (b[1]&1) ? HP(M_ONE) : HP(ONE);//-1^a
				if(abs(a[0]>1 || a[1]>1)){
					if(b[0] > 16) return HP(EMPTY);
				}//结果过大 Result is too large
				vi c = HP_Power(a, HP_VecToll(b));
				return HP(c);
			}
			friend HP HP_pow(HP abi, int bi){
				return HP_pow(abi, HP(bi));
			}
			friend HP HP_pow(HP abi, ll bi){
				return HP_pow(abi, HP(bi));
			}
			friend HP HP_pow(int ai, HP bbi){
				return HP_pow(HP(ai), bbi);
			}
			friend HP HP_pow(ll ai, HP bbi){
				return HP_pow(HP(ai), bbi);
			}
			
			friend int putint(HP cbi);
	};

	//从我的GreatCalculator搬来的高精度计算函数
	//High-precision functions adapted from my GreatCalculator
	vi HP_Plus(vi a, vi b){
	    char za=IntToZF(a[0]), zb=IntToZF(b[0]), zc;
	    int na=abs(a[0]), nb=abs(b[0]);
	    if(za == zb){//同号 same sign
	        if(za=='-' && zb=='-') zc = '-';//(-a)+(-b)=-(a+b)
	        else zc = '+';
	        int nc = max(na, nb); vi c(1, 0);
	        AllResize(nc+5, a, b, c);
	        for(int i=1; i<=nc; i++){
	            c[i] += a[i]+b[i];
	            c[i+1] += c[i]/JW, c[i] %= JW;
	        }
	        if(c[nc+1]) nc++;
	        c[0] = nc*ZFToInt(zc);
	        return c;
	    }
	    else if(za == '-'){
	        VecSwap(a, b);
	        a[0] = abs(a[0]), b[0]=abs(b[0]);
	        return HP_Minus(a, b);
	    }//(-a)+b=b-a
	    else if(zb == '-'){
	        a[0] = abs(a[0]), b[0]=abs(b[0]);
	        return HP_Minus(a, b);
	    }//a+(-b)=a-b
	}
	vi HP_Minus(vi a, vi b){
	    char za=IntToZF(a[0]), zb=IntToZF(b[0]);
	    if(za=='+' && zb=='-'){
	        a[0] = abs(a[0]), b[0]=abs(b[0]);
	        return HP_Plus(a, b);
	    }//a-(-b)=a+b
	    else if(za=='-' && zb=='+'){
	        a[0]=-abs(a[0]), b[0]=-abs(b[0]);
	        return HP_Plus(a, b);
	    }//-a-b = (-a)+(-b)
	    else{
	        //a-b = a-b
	        if(za=='-' && zb=='-'){
	            VecSwap(a, b);//(-a)-(-b) = b-a
	            a[0] = -a[0], b[0]=-b[0];
	        }
	        char zc = '+';
	        if(HP_VecCmp(a, b) < 0){
	            zc = PosiNega(zc);
	            VecSwap(a, b);
	        }
	        int na=abs(a[0]), i;
	        a.resize(na+5), b.resize(na+5);
	        for(i=1; i<=na; i++){
	            a[i] -= b[i];
	            if(a[i] < 0) a[i]+=JW, a[i+1]--;
	        }
	        a[0] = na*ZFToInt(zc);
	        HP_PopFrontZero(a);
	        return a;
	    }
	}
	vi HP_Karatsuba(int n, vi a, vi b){
	    int i, j;
	    vi c(n+n+5, 0);
	    if(n < 32){
	        for(i=1; i<=n; i++)
	            for(j=1; j<=n; j++)
	                c[i+j-1] += a[i]*b[j];
	        return c;
	    }

	    int m = n>>1;
	    vi aa(n-m+5, 0), bb(n-m+5, 0);
	    for(i=1; i<=n-m; i++){
	        aa[i] = a[m+i];
	        bb[i] = b[m+i];
	    }
	    vi z2 = HP_Karatsuba(n-m, aa, bb);
	    vi z0 = HP_Karatsuba(m, a, b);
	    vi as(n-m+5, 0), bs(n-m+5, 0);
	    for(i=1; i<=n-m; i++){
	        as[i] = a[i+m];
	        bs[i] = b[i+m];
	        if(i <= m) {
	            as[i] += a[i];
	            bs[i] += b[i];
	        }
	    }
	    vi z1 = HP_Karatsuba(n-m, as, bs);

	    for(i=1; i<=(n-m<<1); i++){
	        z1[i] -= z2[i];
	        z1[i] -= z0[i];
	    }
	    //c = z2*JW^2m + z1*JW^m + z0
	    for(i=1; i<=(n-m<<1); i++) c[i+m+m] += z2[i];
	    for(i=1; i<=(n-m<<1); i++) c[i+m] += z1[i];
	    for(i=1; i<=(m<<1); i++) c[i] += z0[i];
	    return c;
	}
	vi HP_SimMul(vi a, vi b){
	    char za=IntToZF(a[0]), zb=IntToZF(b[0]);
	    char zc = SymMulti(za, zb);
	    int na=abs(a[0]), nb=abs(b[0]);
	    int nc = na+nb, i, j;
	    a.resize(nc+1, 0);
	    b.resize(nc+1, 0);
	    vi c(nc+5, 0);
	    for(i=1; i<=na; i++)
	        for(j=1; j<=nb; j++)
	            c[i+j-1] += a[i]*b[j];
	    for(j=1; j<=nc; j++) c[j+1] += c[j]/JW, c[j] %= JW;
	    while(c[nc+1]) nc++;
	    c[0] = nc*ZFToInt(zc);
	    HP_PopFrontZero(c);
	    return c;
	}
	vi HP_Multiply(vi a, vi b){
	    char za=IntToZF(a[0]), zb=IntToZF(b[0]);
	    char zc = SymMulti(za, zb);
	    int na=abs(a[0]), nb=abs(b[0]);
	    int nc = na+nb;
	    a.resize(nc+1, 0);
	    b.resize(nc+1, 0);
	    if(na<10 || nb<10) return HP_SimMul(a, b);
	    if((na+na<nb) || (nb+nb<na)) return HP_SimMul(a, b);
	    vi c = HP_Karatsuba(nc, a, b);
	    int limit = c.size()-1;
	    for(int i=1; i<limit; i++){
	        c[i+1] += c[i]/JW, c[i] %= JW;
	        if(c[i] < 0) c[i] += JW, c[i+1]--;
	    }
	    nc = limit;
	    while(nc>1 && !c[nc]) nc--;
	    c.resize(nc + 1);
	    c[0] = nc*ZFToInt(zc);
	    return c;
	}//感谢星星老师和Gemini帮忙调试乘法算法!
	 //Thanks to Teacher Stars and Gemini for helping debug the multiplication algorithm!
	char HP_DivCmp(int r, int n, vi &a, vi &b){
	    if(a[r+n] > 0) return true;
	    if(a[r+n] < 0) return false;
	    for(int i=n; i>0; i--){
	        if(a[r+i-1] > b[i]) return true;
	        if(a[r+i-1] < b[i]) return false;
	    }
	    return true;
	}
	vi HP_Divide(vi a, vi b){
	    char za=IntToZF(a[0]), zb=IntToZF(b[0]);
	    char zc = SymMulti(za, zb);
	    int na=abs(a[0]), nb=abs(b[0]);
	    int nc = max(na, nb);
	    vi c(1, 0);
	    AllResize(nc+5, a, b, c);
	    int i, j;
	    for(i=na-nb+1; i>0; i--){
	        while(HP_DivCmp(i, nb, a, b)){
	            for(j=1; j<=nb; j++){
	                a[i+j-1] -= b[j];
	                if(a[i+j-1] < 0) a[i+j-1]+=JW, a[i+j]--;
	            }
	            c[i]++;
	        }
	    }
	    c[0] = nc*ZFToInt(zc);
	    HP_PopFrontZero(c);
	    return c;
	}
	vi HP_Power(vi a, ll b){
	    vi c = ONE;
		while(b){
			if(b & 1) c = HP_Multiply(c, a), b--;
			else a = HP_Multiply(a, a), b >>= 1;
		}
		return c;
	}
	vi HP_Module(vi a, vi b){
	    int na=abs(a[0]), nb=abs(b[0]);
	    int nc = max(na, nb);
	    a.resize(nc+5), b.resize(nc+5);
	    int i, j;
	    for(i=na-nb+1; i>0; i--){
	        while(HP_DivCmp(i, nb, a, b)){
	            for(j=1; j<=nb; j++){
	                a[i+j-1] -= b[j];
	                if(a[i+j-1] < 0) a[i+j-1]+=JW, a[i+j]--;
	            }
	        }
	    }
	    HP_PopFrontZero(a);
	    return a;
	}

	HP getint(){
		vi a(1, 0);
		int na = 0;// 长度 length
		char za = 0, t;// +-
		while(t = getchar()){
			if(t<=32 && na) break;
			// 读完之后不可见字符 invisible characters after reading in
			if(t == '\n'){//遇到换行符(ASCII < 20) line break (ASCII < 20)
				if(na) break;//已经有数字,输入结束 there have been digits, input ends
				else continue;//还没有数字,继续输入
				//there haven't been digits, continue to input
			}
			if(t == EOF) break;// 输入结束 end of input
			if(IsZF(t)){// 是正负号   the character is a sign
				if(na) break;// 已经开始输入数字了 have started to read in digits
				else if(za) break;// 已经有符号了 have a symbol already
				else za = t;
			}else if(IsFh(t)) break;// 是其他运算符 other calculation characters
			else if(IsDigit(t)){
				a.push_back(t-48);
				na++;
			}//读入数字 read in digits
			else break;//其他字符 other characters
		}
		if(!za) za = '+';
		a[0] = na*ZFToInt(za);
		if(!a[0]) return HP(EMPTY);
		HP_reverse(a);
		a = HP_zip(a);
		return HP(a);
	}
	int putint(HP cbi){
		vi c = HP_unzip(cbi.num);
		char zc = IntToZF(c[0]);
		if(zc == '-') putchar('-');
		int nc = abs(c[0]);
		if(!nc) return 0;//EMPTY
		for(; nc; nc--) putchar(c[nc]+48);
		return 1;//无错误 nothing is wrong
	}
}

#endif