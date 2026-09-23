#include <deque>
#include <iostream>
using namespace std;

int main() {
    deque<int> que;

    que.push_back(1);
    que.push_back(2);
    que.push_back(3);

    while (!que.empty()) {
        cout << que.front() << '\n';
        que.pop_front();
    }

    return 0;
}
