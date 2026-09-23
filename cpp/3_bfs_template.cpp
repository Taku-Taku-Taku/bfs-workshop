#include <deque>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
using namespace std;

int main() {
    // キューの取り出し（TODO 1）を埋めるまでは実行しても終わりません（無限ループ）。
    // 止まらなくなったら Ctrl + C で終了してください。

    int H, W;
    cin >> H >> W;

    int sy, sx;
    int gy, gx;
    cin >> sy >> sx;
    cin >> gy >> gx;

    vector<string> maze(H);
    for (int i = 0; i < H; i++) {
        cin >> maze[i];
    }

    // 各マスまでの距離。-1 は「まだ訪れていない」
    vector<vector<int>> dist(H, vector<int>(W, -1));

    int dy[4] = {-1, 1, 0, 0};
    int dx[4] = {0, 0, -1, 1};

    deque<pair<int, int>> que;

    // スタート地点をキューに入れる
    dist[sy][sx] = 0;
    que.push_back({sy, sx});

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

    int answer = dist[gy][gx];

    if (answer == -1) {
        cout << "ゴールには到達できません\n";
    } else {
        cout << "最短距離: " << answer << '\n';
    }

    return 0;
}
