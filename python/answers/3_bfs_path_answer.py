import sys
from collections import deque

lines = sys.stdin.read().splitlines()
H, W = map(int, lines[0].split())
sy, sx = map(int, lines[1].split())
gy, gx = map(int, lines[2].split())
maze = lines[3:3+H]

# 各マスまでの距離。-1 は「まだ訪れていない」
dist = [[-1] * W for _ in range(H)]

# そのマスへ「どこから来たか」を覚えておく表
py = [[-1] * W for _ in range(H)]
px = [[-1] * W for _ in range(H)]

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

        # (ny, nx) には (y, x) から来た
        py[ny][nx] = y
        px[ny][nx] = x

        que.append((ny, nx))

answer = dist[gy][gx]

if answer == -1:
    print("ゴールには到達できません")
else:
    print("最短距離:", answer)

    # 迷路のコピーを作り、通った道に印をつける
    result = [list(line) for line in maze]

    # ゴールから prev をたどってスタートまで戻る
    y, x = gy, gx

    while (y, x) != (sy, sx):
        result[y][x] = "*"

        back_y = py[y][x]
        back_x = px[y][x]
        y, x = back_y, back_x

    result[sy][sx] = "S"
    result[gy][gx] = "G"

    for line in result:
        print("".join(line))
