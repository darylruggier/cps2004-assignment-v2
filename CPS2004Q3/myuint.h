#ifndef CPS2004_ASSIGNMENT_Q3_MYUINT_H
#define CPS2004_ASSIGNMENT_Q3_MYUINT_H
#include <string>
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>

using namespace std;
template<size_t T>
class myuint {
    public:
    vector<int> bits;
    int n{}; // find a way to make it n bit. e.g. myuint<1024> t or myuint<32> t
    bool isNegative = false;


    explicit myuint<T>(int n) { // t must be of type 2^n. i.e. log_2(n) must be a whole number - if not then throw an exception
        if (floor(log2(T)) != log2(T)) {
            cout << "Invalid Arguments: Size of myuint must be of size 2^n.\n";
            exit(0);
        // compilation error
        } else if ((pow(2, T)-1) < n) { // accounting for overflow
            cout << "Invalid Arguments: Overflow.\n";
            exit(0);
        }

        this->n = n;
        size_t count = 0;
        while (n > 0) { // Converting the number passed through the instance into binary and placing it into vector bits.
            bits.push_back(n%2);
            n /= 2;
            count++;
        }

        for (; count < T; count++) {
            bits.push_back(0); // adding 0s to form the desired myuint size.
        }

        for (int i = bits.size()-1; i >= 0; i--) {
            cout << bits[i];
        }

    }
};


#endif //CPS2004_ASSIGNMENT_Q3_MYUINT_H
