#include<string>
#include <iostream>
#include<vector>
#include<algorithm>
#include<random>
using namespace std;


/*第1题 一个正整数, 如果它能被7整除, 或者它的十进制表示法中某个位数上的数字为7,
则称其为与7相关的数.现求所有小于等于n(n<100)的与7无关的正整数的平方和。*/
/*bool seven(int n) {
    if (n % 7 == 0) {
        return true;
    }
    while (n) {
        if (n % 10 == 7) {
            return true;
        }
        n /= 10;
    }
    return false;
}
int Sum(int n) {
    int sum = 0;
    for (int i = 1;i <= n;i++) {
        if (!seven(i)) {
            sum += i * i;
        }
    }
    return sum;
}
int main(int argc,char const*argv[]) {
    int n;
    cin >> n;
    cout << Sum(n) << endl;
    return 0;
}*/
// 64 位输出请用 printf("%lld")

/*第2题 用小于等于n元去买100只鸡，大鸡5元/只，小鸡3元/只,还有1/3元每只的一种小鸡，分别记为x只,y只,z只。编程求解x,y,z所有可能解。
*/
void cxk(int n) {
    
    for (int x = 0; x <= (n/5); x++) {
        for (int y = 0; y <= (n/3); y++) { // 这里修正为 n - x
            for (int z = 0;z <= (n/(1.0/3.0));z++) {
                if (x + y + z == 100 && (5 * x + 3 * y + (1.0 / 3.0) * z)<= n) {
                cout << "x=" << x << "," << "y=" << y << "," << "z=" << z << endl;
            }
            }
        }
    }
}

int main(int argc,char const*argv[]) {
    int n;
    cin >> n;
    cxk(n);
    return 0;
}
