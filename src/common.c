#include "common.h"


int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int mod(int a, int b) {
    return (a % b + b) % b;
}
