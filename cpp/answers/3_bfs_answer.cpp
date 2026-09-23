#include <deque>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
using namespace std;

int main() {
    int H, W;
    cin >> H >> W;

    int start_row, start_col;
    int goal_row, goal_col;
    cin >> start_row >> start_col;
    cin >> goal_row >> goal_col;

    vector<string> maze(H);
    for (int i = 0; i < H; i++) {
        cin >> maze[i];
    }

    // 各マスまでの距離。-1 は「まだ訪れていない」
    vector<vector<int>> dist(H, vector<int>(W, -1));

    int dr[4] = {-1, 1, 0, 0};
    int dc[4] = {0, 0, -1, 1};

    deque<pair<int, int>> que;

    // スタート地点をキューに入れる
    dist[start_row][start_col] = 0;
    que.push_back({start_row, start_col});

    while (!que.empty()) {
        auto [row, col] = que.front();
        que.pop_front();

        for (int i = 0; i < 4; i++) {
            int next_row = row + dr[i];
            int next_col = col + dc[i];

            if (next_row < 0 || next_row >= H ||
                next_col < 0 || next_col >= W) {
                continue;
            }

            if (maze[next_row][next_col] == '#') {
                continue;
            }

            if (dist[next_row][next_col] != -1) {
                continue;
            }

            dist[next_row][next_col] = dist[row][col] + 1;
            que.push_back({next_row, next_col});
        }
    }

    int answer = dist[goal_row][goal_col];

    if (answer == -1) {
        cout << "ゴールには到達できません\n";
    } else {
        cout << "最短距離: " << answer << '\n';
    }

    return 0;
}
