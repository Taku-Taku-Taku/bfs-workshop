#include <iostream>
#include <queue>
#include <string>
#include <utility>
#include <vector>
using namespace std;

int main() {
    vector<string> maze = {
        "........",
        ".####...",
        "....#...",
        ".##.....",
        "........",
    };

    int H = (int)maze.size();
    int W = (int)maze[0].size();

    int start_row = 0;
    int start_col = 0;
    int goal_row = 4;
    int goal_col = 7;

    // 各マスまでの距離。-1 は「まだ訪れていない」
    vector<vector<int>> dist(H, vector<int>(W, -1));

    int dr[4] = {-1, 1, 0, 0};
    int dc[4] = {0, 0, -1, 1};

    queue<pair<int, int>> que;

    // スタート地点をキューに入れる
    dist[start_row][start_col] = 0;
    que.push({start_row, start_col});

    while (!que.empty()) {
        auto [row, col] = que.front();
        que.pop();

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
            que.push({next_row, next_col});
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
