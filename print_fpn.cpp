#include <iostream>
#include <unordered_set>

using namespace std;

int find_repeat(int n, int d) {
    unordered_set<int> found;
    while(n && found.find(n) == found.end()) {
        found.insert(n);
        n = n % d * 10;
    }
    return n;
}

void print_fpn(int n, int d) {
    cout << n / d << '.';
    n = n % d * 10;
    int r = find_repeat(n, d);
    bool found = false;
    while(true) {
        if(n == r) {
            if(found) {
                cout << ')' << endl;
                return;
            }
            else {
                cout << '(';
                found = true;
            }
        }
        cout << n / d;
        n = n % d * 10;
    }
}

int main() {
    int n, d;
    cin >> n >> d;
    print_fpn(n, d);
    return 0;
}
