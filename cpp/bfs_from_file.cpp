#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <utility>
#include <vector>
using namespace std;

int main() {
    // 読み込む迷路ファイル（ここを書き換えると別の迷路を試せます）
    string maze_file = "maze02.txt";

    ifstream fin("../mazes/" + maze_file);

    if (!fin) {
        cerr << "迷路ファイルを開けません: ../mazes/" << maze_file << '\n';
        cerr << "cpp ディレクトリに移動してから実行してください\n";
        return 1;
    }

    int H, W;
    fin >> H >> W;

    int start_row, start_col;
    int goal_row, goal_col;
    fin >> start_row >> start_col;
    fin >> goal_row >> goal_col;

    vector<string> maze(H);
    for (int i = 0; i < H; i++) {
        fin >> maze[i];
    }

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

    cout << maze_file << '\n';

    if (answer == -1) {
        cout << "ゴールには到達できません\n";
    } else {
        cout << "最短距離: " << answer << '\n';
    }

    return 0;
}
