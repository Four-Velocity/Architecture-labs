#include <iostream>
#include <string>
using namespace std;

int power(int x, int p) {
    if (p == 0) return 1;
    if (p == 1) return x;
    return x * power(x,p-1);
}

int translate_to_ten(int number, int base) {
    int result = 0;
    for(int i = 0; number; i++) {
        int pow = power(base, i);
        int part = number % 10;
        if (part >= base) throw runtime_error("Unacceptable digits for this base");
        result += part * pow;
        number /= 10;
    }
    return result;
}

int translate_to_base(int number, int base, int result=0, int scale=1) {
    if (number>=base) {
        int next = number / base;
        result += (number % base) * scale;
        scale *= 10;
        return translate_to_base(next, base, result, scale);
    } else {
        result += number * scale;
        return result;
    }
}

int main() {
    int base9_number, base7_number, base10_number;
    char checker;
    cout << "Enter your number:  ";
    cin >> base9_number;
    cout << "" << endl;
    try {
        base10_number = translate_to_ten(base9_number, 9);
        base7_number = translate_to_base(base10_number, 7);
        cout << "Base 9  number: " << base9_number << endl;
        cout << "Base 7  number: " << base7_number << endl;
        cout << "Base 10 number: " << base10_number << endl;
    } catch (runtime_error e) {
        cout << "Runtime error: " << e.what();
    }
    return 0;
}
