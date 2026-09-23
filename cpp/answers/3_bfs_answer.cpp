#include <deque>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
using namespace std;

int main() {
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
        auto [y, x] = que.front();
        que.pop_front();

        for (int i = 0; i < 4; i++) {
            int ny = y + dy[i];
            int nx = x + dx[i];

            if (ny < 0 || ny >= H ||
                nx < 0 || nx >= W) {
                continue;
            }

            if (maze[ny][nx] == '#') {
                continue;
            }

            if (dist[ny][nx] != -1) {
                continue;
            }

            dist[ny][nx] = dist[y][x] + 1;
            que.push_back({ny, nx});
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
