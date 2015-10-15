#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

bool canimmunize(const vector<int>& population, int num_clinics, int max_kits) {
    int n = 0;
    for(auto& p: population) {
        int m = (p + max_kits - 1) / max_kits;
        n += m;
    }
    return n <= num_clinics;
}

int solve(const vector<int>& population, int num_clinics) {
    int min = 0, max = 5000000;
    while(min + 1 < max) {
        int mid = (min + max) / 2;
        if(canimmunize(population, num_clinics, mid))
            max = mid;
        else
            min = mid;
    }
    return max;
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int N, B;
    cin >> N >> B;
    vector<int> population(N);
    for(auto& p : population)
        cin >> p;
    cout << solve(population, B) << endl;
    return 0;
}
