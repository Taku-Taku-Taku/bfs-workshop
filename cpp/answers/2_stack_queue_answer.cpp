#include <iostream>
#include <queue>
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

    queue<int> que;

    que.push(10);
    que.push(20);
    que.push(30);
    que.push(40);

    while (!que.empty()) {
        cout << que.front() << '\n';
        que.pop();
    }

    return 0;
}
