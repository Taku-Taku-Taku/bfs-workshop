import os
from collections import deque

# 読み込む迷路ファイル（ここを書き換えると別の迷路を試せます）
maze_file = "maze02.txt"

# このプログラムの場所を基準に ../mazes/ を開く（どこから実行しても動くように）
path = os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "mazes", maze_file)

with open(path, encoding="utf-8") as f:
    H, W = map(int, f.readline().split())
    sy, sx = map(int, f.readline().split())
    gy, gx = map(int, f.readline().split())
    maze = [f.readline().strip() for _ in range(H)]

# 各マスまでの距離。-1 は「まだ訪れていない」
dist = [[-1] * W for _ in range(H)]

dy = [-1, 1, 0, 0]
dx = [0, 0, -1, 1]

que = deque()

# スタート地点をキューに入れる
dist[sy][sx] = 0
que.append((sy, sx))

while que:
    y, x = que.popleft()

    for i in range(4):
        ny = y + dy[i]
        nx = x + dx[i]

        if not (0 <= ny < H and 0 <= nx < W):
            continue

        if maze[ny][nx] == "#":
            continue

        if dist[ny][nx] != -1:
            continue

        dist[ny][nx] = dist[y][x] + 1
        que.append((ny, nx))

answer = dist[gy][gx]

print(maze_file)

if answer == -1:
    print("ゴールには到達できません")
else:
    print("最短距離:", answer)
