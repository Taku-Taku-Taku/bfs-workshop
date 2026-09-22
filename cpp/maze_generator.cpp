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

    int dr[4] = {-2, 2, 0, 0};
    int dc[4] = {0, 0, -2, 2};

    random_device rd;
    mt19937 rng(rd());

    vector<pair<int, int>> st;
    st.push_back({1, 1});
    maze[1][1] = '.';

    while (!st.empty()) {
        auto [row, col] = st.back();

        vector<pair<int, int>> candidates;

        for (int i = 0; i < 4; i++) {
            int nr = row + dr[i];
            int nc = col + dc[i];

            if (nr < 1 || nr >= H - 1 || nc < 1 || nc >= W - 1) {
                continue;
            }

            if (maze[nr][nc] == '.') {
                continue;
            }

            candidates.push_back({nr, nc});
        }

        if (candidates.empty()) {
            st.pop_back();
            continue;
        }

        shuffle(candidates.begin(), candidates.end(), rng);
        auto [nr, nc] = candidates[0];

        int wall_row = (row + nr) / 2;
        int wall_col = (col + nc) / 2;

        maze[wall_row][wall_col] = '.';
        maze[nr][nc] = '.';

        st.push_back({nr, nc});
    }

    vector<pair<int, int>> roads;

    for (int r = 0; r < H; r++) {
        for (int c = 0; c < W; c++) {
            if (maze[r][c] == '.') {
                roads.push_back({r, c});
            }
        }
    }

    shuffle(roads.begin(), roads.end(), rng);

    auto [start_row, start_col] = roads[0];
    auto [goal_row, goal_col] = roads[1];

    cout << H << ' ' << W << '\n';
    cout << start_row << ' ' << start_col << '\n';
    cout << goal_row << ' ' << goal_col << '\n';

    for (const string& row : maze) {
        cout << row << '\n';
    }

    return 0;
}
