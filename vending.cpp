#include <iostream>
#include <array>

using namespace std;

constexpr size_t N = 3;

int low[N] = {5, 1, 3};
int high[N] = {10, 3, 7};

int target_low = 10;
int target_high = 30;

void solve(int l, int h, int b, array<int, N>& pressed) {
    if(target_high < h || b == N)
        return;

    pressed[b]++;
    if(target_low <= (l + low[b]) && (h + high[b]) <= target_high) {
        for(auto& e: pressed)
            cout << e << ", ";
        cout << (l + low[b]) << ":" << (h + high[b]) << endl;
    }
    solve(l + low[b], h + high[b], b, pressed);
    pressed[b]--;
    solve(l, h, b+1, pressed);
}

int main() {
    array<int, N> pressed = {0};
    solve(0, 0, 0, pressed);
    return 0;
}
