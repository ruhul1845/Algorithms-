/*
 * Bit Manipulation - Basic Operations
 * Bitwise operators, common patterns, and tricks
 */

#include <bits/stdc++.h>
using namespace std;

// 1. Check if Kth bit is set
bool isKthBitSet(int n, int k) {
    return (n & (1 << k)) != 0;
}

// 2. Set Kth bit
int setKthBit(int n, int k) {
    return n | (1 << k);
}

// 3. Clear Kth bit
int clearKthBit(int n, int k) {
    return n & ~(1 << k);
}

// 4. Toggle Kth bit
int toggleKthBit(int n, int k) {
    return n ^ (1 << k);
}

// 5. Count Set Bits (Brian Kernighan's Algorithm)
int countSetBits(int n) {
    int count = 0;
    while (n) {
        n = n & (n - 1); // Remove rightmost set bit
        count++;
    }
    return count;
}

// 6. Check if Power of Two
bool isPowerOfTwo(int n) {
    return n > 0 && (n & (n - 1)) == 0;
}

// 7. Count Total Bits
int countBits(int n) {
    return (int)log2(n) + 1;
}

// 8. Position of Rightmost Set Bit
int rightmostSetBit(int n) {
    if (n == 0) return -1;
    return log2(n & -n) + 1;
}

// 9. Turn off Rightmost Set Bit
int turnOffRightmostSetBit(int n) {
    return n & (n - 1);
}

// 10. Check if numbers have opposite signs
bool oppositeSigns(int x, int y) {
    return (x ^ y) < 0;
}

// 11. Swap two numbers without temp
void swapNumbers(int& a, int& b) {
    if (a != b) {
        a = a ^ b;
        b = a ^ b;
        a = a ^ b;
    }
}

// 12. Find missing number (XOR trick)
int findMissing(vector<int>& arr, int n) {
    int xorAll = 0;
    int xorArr = 0;
    
    for (int i = 1; i <= n; i++) {
        xorAll ^= i;
    }
    
    for (int num : arr) {
        xorArr ^= num;
    }
    
    return xorAll ^ xorArr;
}

// 13. Single Number (All others appear twice)
int singleNumber(vector<int>& nums) {
    int result = 0;
    for (int num : nums) {
        result ^= num;
    }
    return result;
}

// 14. Two numbers appearing once (others twice)
vector<int> singleNumber3(vector<int>& nums) {
    int xorAll = 0;
    for (int num : nums) {
        xorAll ^= num;
    }
    
    // Find rightmost set bit
    int rightBit = xorAll & -xorAll;
    
    int x = 0, y = 0;
    for (int num : nums) {
        if (num & rightBit) {
            x ^= num;
        } else {
            y ^= num;
        }
    }
    
    return {x, y};
}

// 15. Single Number II (All others appear thrice)
int singleNumber2(vector<int>& nums) {
    int ones = 0, twos = 0;
    
    for (int num : nums) {
        twos |= ones & num;
        ones ^= num;
        
        int threes = ones & twos;
        ones &= ~threes;
        twos &= ~threes;
    }
    
    return ones;
}

// 16. Reverse Bits
uint32_t reverseBits(uint32_t n) {
    uint32_t result = 0;
    for (int i = 0; i < 32; i++) {
        result <<= 1;
        result |= (n & 1);
        n >>= 1;
    }
    return result;
}

// 17. Number of 1 Bits (Hamming Weight)
int hammingWeight(uint32_t n) {
    int count = 0;
    while (n) {
        count += n & 1;
        n >>= 1;
    }
    return count;
}

// 18. Add two numbers using bits
int add(int a, int b) {
    while (b != 0) {
        int carry = a & b;
        a = a ^ b;
        b = carry << 1;
    }
    return a;
}

// 19. Subtract using bits
int subtract(int a, int b) {
    while (b != 0) {
        int borrow = (~a) & b;
        a = a ^ b;
        b = borrow << 1;
    }
    return a;
}

// 20. Multiply using bits
int multiply(int a, int b) {
    int result = 0;
    while (b > 0) {
        if (b & 1) {
            result = add(result, a);
        }
        a <<= 1;
        b >>= 1;
    }
    return result;
}

void printBinary(int n) {
    for (int i = 31; i >= 0; i--) {
        cout << ((n >> i) & 1);
    }
    cout << endl;
}

int main() {
    int n = 13; // Binary: 1101
    
    cout << "Number: " << n << " (Binary: ";
    printBinary(n);
    cout << ")" << endl;
    
    cout << "Count set bits: " << countSetBits(n) << endl;
    cout << "Is 2nd bit set? " << (isKthBitSet(n, 2) ? "Yes" : "No") << endl;
    cout << "Set 1st bit: " << setKthBit(n, 1) << endl;
    cout << "Clear 0th bit: " << clearKthBit(n, 0) << endl;
    cout << "Toggle 3rd bit: " << toggleKthBit(n, 3) << endl;
    
    cout << "\nIs 16 power of 2? " << (isPowerOfTwo(16) ? "Yes" : "No") << endl;
    cout << "Is 18 power of 2? " << (isPowerOfTwo(18) ? "Yes" : "No") << endl;
    
    vector<int> arr = {2, 3, 5, 4, 5, 3, 4};
    cout << "\nSingle number in array: " << singleNumber(arr) << endl;
    
    cout << "\nAdd 5 + 7 using bits: " << add(5, 7) << endl;
    cout << "Multiply 3 * 4 using bits: " << multiply(3, 4) << endl;
    
    return 0;
}










