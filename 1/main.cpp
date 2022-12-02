#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <numeric>
using namespace std;

int main(){
    vector<long long> elves = {0};
    string s;

    while(getline(cin, s)){
        if(s.empty()){
            elves.push_back(0);
        } else {
            elves.back() += stoll(s);
        }
    }

    sort(elves.begin(), elves.end());

    cout << "Part 1: " << elves.back() << endl;
    cout << "Part 2: " << std::accumulate(elves.end() - 3, elves.end(), 0) << endl;
}

