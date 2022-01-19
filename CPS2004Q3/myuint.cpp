#include "myuint.h"
#include <algorithm>
using namespace std;

vector<int> decimalToBin(int n) { // Function used to avoid boilerplate code
    vector<int> bits;
    size_t count = 0;

    while (n > 0) { // Converting the number passed through the instance into binary and placing it into vector bits.
        bits.push_back(n%2);
        n /= 2;
        count++;
    }

    while (n < 0) { // Converting the number passed through the instance into binary and placing it into vector bits.
        bits.push_back(-n%2);
        n /= 2;
        count++;
    }
    return bits;
}


template<size_t T>
int binToDecimal(myuint<T> n) { // Conversion from myuint<T> to int.
    int output = 0;
    int power = 1;

    for (int i = 0; i < n.bits.size(); i++) {
        if (n.isNegative && i == n.bits.size() - 1) { // setting MSB to - if the myuint is negative (for two's complement)
            output += n.bits[i] * -power;
            continue;
        }
        output += n.bits[i] * power;
        power *= 2;
    }
    return output;
}

// << (shift left) : shift elements of the vector to the left n times (n denoted by the shift amount)
// >> (shift right) : shift elements of the vector to the right n times (n denoted by the shift amount)
template<size_t T>
myuint<T> operator>>(myuint<T> n, int b) { // shifts vector<int> a.bits (of myuint a) to the left b times
    // Rotating the bits and then setting them to 0. the shift_left() function from the <algorithm> header
    // is more efficient, however it was not being recognised, even after checking the cpp version.

    rotate(n.bits.begin(), n.bits.begin() + b, n.bits.end()); // Rotating the bits b times to the right (passed through the operator arguments)
    for (int i = n.bits.size()-1; i >= n.bits.size() - b; i--) { // Setting the rotated bits to zero immediately after rotating. Thus, the shifting operation is done.
        n.bits[i] = 0;
    }
    return n;
}

template<size_t T>
myuint<T> operator<<(myuint<T> n, int b) { // shifts vector<int> a.bits (of myuint a) to the left b times
    // Rotating the bits and then setting them to 0. the shift_left() function from the <algorithm> header
    // is more efficient, however it was not being recognised, even after checking the cpp version.

    rotate(n.bits.begin(), n.bits.begin() + n.bits.size() - b, n.bits.end()); // Rotating the bits b times to the left.
    for (int i = 0; i < b; i++) { // Setting the rotated bits to zero immediately after rotating. Thus, the shifting operation is done.
        n.bits[i] = 0;
    }
    return n;
}


template<size_t T>
myuint<T> operator+(myuint<T> a, int b) { // adds together myuint a and int b
    vector<int> bits;
    vector<int> result;
    bool isNegative = false;

    if (b < 0) {
        b = -b;
        isNegative = true;
    }

    if (binToDecimal(a) < b) {
        a.isNegative = true;
    }

    bits = decimalToBin(b);
    // Calculating the two's complement of b if it is negative.
    if (isNegative) {
        int stop = 0;
        for (int i = 0; i < bits.size(); i++) {
            if (bits[i] == 1) {
                stop = i;
                break;
            }
        }

        int a_size_minus_b_size = a.bits.size() - bits.size();
        for (int i = 0; i < a_size_minus_b_size; i++) { // Appending 0s to the number to be subtracted, to match the number of bits of the myuint. (e.g. 3: 11 -> 0011). This is done so that the addition functions work smoothly (avoiding any nullpointer exceptions)
            bits.insert(bits.end(), 0);
        }

        for (int i = stop+1; i < bits.size(); i++) {
            bits[i] == 0 ? bits[i] = 1 : bits[i] = 0; // flipping the 1s and 0s after the first 1 is found.
        }
    } // problem: bits numbers being inserted the wrong way. (e.g. -3 should be {1, 1, 0, 0} not {0, 0, 1, 1}

    int size = (a.bits.size() > bits.size()) ? a.bits.size() : bits.size();
    int carry = 0;

    for (int i = 0; i < size; i++) {
        int bitA = i < a.bits.size() && a.bits[i] ? 1 : 0; // test if bit in array a is set
        int bitB = i < bits.size() && bits[i] ? 1 : 0; // test if bit in array b is set
        int sum = bitA + bitB + carry; // calculate sum of all bits
        result.push_back(sum == 1 || sum == 3 ? 1 : 0); // result bit is set if sum is equal 1 or 3
        carry = sum > 1 ? 1 : 0; // carry bit is set if sum is equal 2 or 3
    }

    if (carry == 1 && !isNegative) { // Creates a new bit to account for overflow. (e.g. 15 + 1 = 1111 + 1 = 10000, so another bit is added to avoid overflow)
        result.push_back(0);
        result[size] = carry;
    }
    a.bits.clear();

    for (int & i : result) {
        a.bits.push_back(i);
    }
    return a;
}

template<size_t T>
myuint<T> operator-(myuint<T> a, int b) { // subtracts int b from myuint a
    return a + (-b); // calls + operator (e.g. 1 - 2 = 1 + (-2)).
}

template<size_t T>
myuint<T> operator*(myuint<T> a, int b) { // multiplies together myuint a and b.
    //Step 1: convert a.bits vector into integer.
    //Step 2: Carry out the integer multiplication between the a.bits vector conversion and b.
    //Step 3: Convert the result of the multiplication into binary and place it into the vector.
    //Step 4: return the myuint
    int a_convertedToInt = binToDecimal(a.bits);

    int ans = 0, count = 0;
    while (a_convertedToInt)
    {
        // check for set bit and left
        // shift n, count times
        if (a_convertedToInt % 2 == 1)
            ans += b << count;

        // increment of place value (count)
        count++;
        a_convertedToInt /= 2;
    }
    vector<int> result = decimalToBin(ans);

    int a_size_minus_b_size = a.bits.size() - result.size();
    for (int i = 0; i < a_size_minus_b_size; i++) { // Appending 0s to match the number of bits of the myuint.
        result.insert(result.end(), 0);
    }

    //Replacing a.bits with the result after multiplying.
    a.bits.clear();
    for (int &i : result) {
        a.bits.push_back(i);
    }
    return a;
}

template<size_t T>
myuint<T> operator/(myuint<T> a, int b) { // divides myuint a with b.
    //Step 1: convert a.bits into decimal
    //Step 2: carry out integer division between the integer value of a.bits and int b.
    //Step 3: convert the result into binary and place into a.bits
    int a_convertedToDecimal = binToDecimal(a);
    int div_result = a_convertedToDecimal / b;
    vector<int> result = decimalToBin(div_result);

    int a_size_minus_result_size = a.bits.size() - result.size();
    for (int i = 0; i < a_size_minus_result_size; i++) { // Appending 0s to match the number of bits of the myuint.
        result.insert(result.end(), 0);
    }

    //Replacing a.bits with the result after dividing.
    a.bits.clear();
    for (int &i : result) {
        a.bits.push_back(i);
    }
    return a;
}

template<size_t T>
myuint<T> operator%(myuint<T> a, int b) { // finds the remainder of myuint a and int b.
    //step 1: convert a.bits to decimal
    //step 2: calculate a_convertedToDecimal % b
    //step 3: convert result into binary and place into a
    int a_convertedToDecimal = binToDecimal(a);
    int mod_result = a_convertedToDecimal % b;
    vector<int> result = decimalToBin(mod_result);

    int a_size_minus_result_size = a.bits.size() - result.size();
    for (int i = 0; i < a_size_minus_result_size; i++) { // Appending 0s to match the number of bits of the myuint.
        result.insert(result.end(), 0);
    }

    //Replacing a.bits with the result after calculating the mod result.
    a.bits.clear();
    for (int &i : result) {
        a.bits.push_back(i);
    }
    return a;
}

template<size_t T>
myuint<T> operator+(myuint<T> a, myuint<T> b) { // adds together myuint a and myuint b (this function was not required, hence not too much testing was done on it)
    myuint<T> c;
    int size = (a.bits.size > b.bits.size) ? a : b; // creating a new myuint<T> c which houses the smaller of the 2 myuints to be added.
    int carry = 0;

    for (int i = 0; i < size; i++) {
        int bitA = i < a.bits.size() && a.bits[i] ? 1 : 0; // test if bit in array a is set
        int bitB = i < b.bits.size() && b.bits[i] ? 1 : 0; // test if bit in array b is set
        int sum = bitA + bitB + carry; // calculate sum of all bits
        c.bits.push_back(sum == 1 || sum == 3 ? 1 : 0); // result bit is set if sum is equal 1 or 3
        carry = sum > 1 ? 1 : 0; // carry bit is set if sum is equal 2 or 3
    }

    c.bits.push_back(0);
    c.bits[size] = carry;
    return c;
}

int binToDecimal(vector<int> bits) { // Conversion from bin to int, used further in the operator functions so as to avoid boilerplate code.
    int output = 0;
    int power = 1;

    for (int i = 0; i < bits.size(); i++) {

        output += bits[i] * power;
        power *= 2;
    }
    return output;
}