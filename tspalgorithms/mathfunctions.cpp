#include "mathfunctions.h"

unsigned long long math::newton(unsigned long long n, unsigned long long k) {
    if(k > n)
        return 0;
    if(k == n || k == 0)
        return 1;
    unsigned long long effectiveK = k > n - k ? k : n - k;
    unsigned long long result = 1;
    for(unsigned long long i = 0; i < effectiveK; ){
        result *= (n - i++);
        result /= i;
    }
    return result;
}