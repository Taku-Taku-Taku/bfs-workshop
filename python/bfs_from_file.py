import os
from collections import deque

# 読み込む迷路ファイル（ここを書き換えると別の迷路を試せます）
maze_file = "maze02.txt"

# このプログラムの場所を基準に ../mazes/ を開く（どこから実行しても動くように）
path = os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "mazes", maze_file)

with open(path, encoding="utf-8") as f:
    H, W = map(int, f.readline().split())
    start_row, start_col = map(int, f.readline().split())
    goal_row, goal_col = map(int, f.readline().split())
    maze = [f.readline().strip() for _ in range(H)]

# 各マスまでの距離。-1 は「まだ訪れていない」
dist = [[-1] * W for _ in range(H)]

dr = [-1, 1, 0, 0]
dc = [0, 0, -1, 1]

que = deque()

# スタート地点をキューに入れる
dist[start_row][start_col] = 0
que.append((start_row, start_col))

while que:
    row, col = que.popleft()

    for i in range(4):
        next_row = row + dr[i]
        next_col = col + dc[i]

        if not (0 <= next_row < H and 0 <= next_col < W):
            continue

        if maze[next_row][next_col] == "#":
            continue

        if dist[next_row][next_col] != -1:
            continue

        dist[next_row][next_col] = dist[row][col] + 1
        que.append((next_row, next_col))

answer = dist[goal_row][goal_col]

print(maze_file)

if answer == -1:
    print("ゴールには到達できません")
else:
    print("最短距離:", answer)
