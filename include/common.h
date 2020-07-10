#pragma once

int mod(int a, int b) {
    const int c = a % b;
    return c >= 0 ? c : c + b;
}
