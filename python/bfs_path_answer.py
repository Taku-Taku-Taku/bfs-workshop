from collections import deque

maze = [
    "........",
    ".####...",
    "....#...",
    ".##.....",
    "........",
]

H = len(maze)
W = len(maze[0])

start_row, start_col = 0, 0
goal_row, goal_col = 4, 7

# 各マスまでの距離。-1 は「まだ訪れていない」
dist = [[-1] * W for _ in range(H)]

# そのマスへ「どこから来たか」を覚えておく表
prev_row = [[-1] * W for _ in range(H)]
prev_col = [[-1] * W for _ in range(H)]

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

        # (next_row, next_col) には (row, col) から来た
        prev_row[next_row][next_col] = row
        prev_col[next_row][next_col] = col

        que.append((next_row, next_col))

answer = dist[goal_row][goal_col]

if answer == -1:
    print("ゴールには到達できません")
else:
    print("最短距離:", answer)

    # 迷路のコピーを作り、通った道に印をつける
    result = [list(line) for line in maze]

    # ゴールから prev をたどってスタートまで戻る
    row, col = goal_row, goal_col

    while (row, col) != (start_row, start_col):
        result[row][col] = "*"

        back_row = prev_row[row][col]
        back_col = prev_col[row][col]
        row, col = back_row, back_col

    result[start_row][start_col] = "S"
    result[goal_row][goal_col] = "G"

    for line in result:
        print("".join(line))
