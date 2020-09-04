#include "common.h"

int mod(int a, int b) {
    const int c = a % b;
    return c >= 0 ? c : c + b;
}

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
}
