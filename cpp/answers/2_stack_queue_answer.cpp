#include <deque>
#include <iostream>
#include <stack>
using namespace std;

int main() {
    stack<int> st;

    st.push(10);
    st.push(20);
    st.push(30);
    st.push(40);

    while (!st.empty()) {
        cout << st.top() << '\n';
        st.pop();
    }

    cout << "-----\n";

    deque<int> que;

    que.push_back(10);
    que.push_back(20);
    que.push_back(30);
    que.push_back(40);

    while (!que.empty()) {
        cout << que.front() << '\n';
        que.pop_front();
    }

    return 0;
}
