#include <algorithm>
#include <iostream>
#include <random>
#include <string>
#include <utility>
#include <vector>
using namespace std;

int main() {
    const int H = 21;
    const int W = 31;

    if (H % 2 == 0 || W % 2 == 0) {
        cerr << "H, W は奇数にしてください\n";
        return 1;
    }

    vector<string> maze(H, string(W, '#'));

    int dy[4] = {-2, 2, 0, 0};
    int dx[4] = {0, 0, -2, 2};

    random_device rd;
    mt19937 rng(rd());

    vector<pair<int, int>> st;
    st.push_back({1, 1});
    maze[1][1] = '.';

    while (!st.empty()) {
        auto [y, x] = st.back();

        vector<pair<int, int>> candidates;

        for (int i = 0; i < 4; i++) {
            int ny = y + dy[i];
            int nx = x + dx[i];

            if (ny < 1 || ny >= H - 1 || nx < 1 || nx >= W - 1) {
                continue;
            }

            if (maze[ny][nx] == '.') {
                continue;
            }

            candidates.push_back({ny, nx});
        }

        if (candidates.empty()) {
            st.pop_back();
            continue;
        }

        shuffle(candidates.begin(), candidates.end(), rng);
        auto [ny, nx] = candidates[0];

        int wy = (y + ny) / 2;
        int wx = (x + nx) / 2;

        maze[wy][wx] = '.';
        maze[ny][nx] = '.';

        st.push_back({ny, nx});
    }

    vector<pair<int, int>> roads;

    for (int y = 0; y < H; y++) {
        for (int x = 0; x < W; x++) {
            if (maze[y][x] == '.') {
                roads.push_back({y, x});
            }
        }
    }

    shuffle(roads.begin(), roads.end(), rng);

    auto [sy, sx] = roads[0];
    auto [gy, gx] = roads[1];

    maze[sy][sx] = 'S';
    maze[gy][gx] = 'G';

    cout << H << ' ' << W << '\n';
    cout << sy << ' ' << sx << '\n';
    cout << gy << ' ' << gx << '\n';

    for (const string& line : maze) {
        cout << line << '\n';
    }

    return 0;
}
