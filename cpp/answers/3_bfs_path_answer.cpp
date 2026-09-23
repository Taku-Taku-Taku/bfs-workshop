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

    // そのマスへ「どこから来たか」を覚えておく表
    vector<vector<int>> py(H, vector<int>(W, -1));
    vector<vector<int>> px(H, vector<int>(W, -1));

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

            // (ny, nx) には (y, x) から来た
            py[ny][nx] = y;
            px[ny][nx] = x;

            que.push_back({ny, nx});
        }
    }

    int answer = dist[gy][gx];

    if (answer == -1) {
        cout << "ゴールには到達できません\n";
    } else {
        cout << "最短距離: " << answer << '\n';

        // 迷路のコピーを作り、通った道に印をつける
        vector<string> result = maze;

        // ゴールから prev をたどってスタートまで戻る
        int y = gy;
        int x = gx;

        while (y != sy || x != sx) {
            result[y][x] = '*';

            int back_y = py[y][x];
            int back_x = px[y][x];
            y = back_y;
            x = back_x;
        }

        result[sy][sx] = 'S';
        result[gy][gx] = 'G';

        for (const string& line : result) {
            cout << line << '\n';
        }
    }

    return 0;
}
