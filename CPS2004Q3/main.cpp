#include <iostream>
#include "myuint.cpp"

using namespace std;
int main() {
    myuint<8> a(72);
    cout << "\n";
    myuint<8> c = (((a / 2) - 3) * 7) % 16;
    for (int j = c.bits.size() - 1; j >= 0; j--) {
        cout << c.bits[j];
    }

    cout << "\nconverted to int: " << binToDecimal(c) << "\n";
}
