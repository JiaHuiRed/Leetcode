#include<string>
#include <iostream>
#include<vector>
#include<algorithm>
#include<random>
using namespace std;


/*��1�� һ��������, ������ܱ�7����, ��������ʮ���Ʊ�ʾ����ĳ��λ���ϵ�����Ϊ7,
�����Ϊ��7��ص���.��������С�ڵ���n(n<100)����7�޹ص���������ƽ���͡�*/
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
// 64 λ������� printf("%lld")

/*��2�� ��С�ڵ���nԪȥ��100ֻ������5Ԫ/ֻ��С��3Ԫ/ֻ,����1/3Ԫÿֻ��һ��С�����ֱ��Ϊxֻ,yֻ,zֻ��������x,y,z���п��ܽ⡣
*/
void cxk(int n) {
    
    for (int x = 0; x <= (n/5); x++) {
        for (int y = 0; y <= (n/3); y++) { // ��������Ϊ n - x
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
