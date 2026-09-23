#include <deque>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
using namespace std;

int main() {
    // キューの取り出し（TODO 1）を埋めるまでは実行しても終わりません（無限ループ）。
    // 止まらなくなったら Ctrl + C で終了してください。

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

    deque<pair<int, int>> que;

    // スタート地点をキューに入れる
    dist[start_row][start_col] = 0;
    que.push_back({start_row, start_col});

    while (!que.empty()) {
        // TODO 1:
        // キューの先頭から現在地を取り出し、キューから削除しよう


        for (int i = 0; i < 4; i++) {
            // TODO 2:
            // 次に移動する座標を求めよう


            // TODO 3:
            // 迷路の外ならスキップしよう


            // TODO 4:
            // 壁ならスキップしよう


            // TODO 5:
            // すでに訪問済みならスキップしよう


            // TODO 6:
            // 現在地から1手進んだ距離を記録しよう


            // TODO 7:
            // 次の場所をキューに追加しよう

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
