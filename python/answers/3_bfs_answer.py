import sys
from collections import deque

lines = sys.stdin.read().splitlines()
H, W = map(int, lines[0].split())
sy, sx = map(int, lines[1].split())
gy, gx = map(int, lines[2].split())
maze = lines[3:3+H]

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

if answer == -1:
    print("ゴールには到達できません")
else:
    print("最短距離:", answer)
