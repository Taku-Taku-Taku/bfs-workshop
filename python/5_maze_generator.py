import random

# 奇数サイズを推奨
H = 21
W = 31

if H % 2 == 0 or W % 2 == 0:
    raise ValueError("H, W は奇数にしてください")

maze = [["#"] * W for _ in range(H)]

# 1マス飛ばしで進み、間の壁も壊す
dr = [-2, 2, 0, 0]
dc = [0, 0, -2, 2]

start = (1, 1)
stack = [start]
maze[1][1] = "."

while stack:
    row, col = stack[-1]

    candidates = []

    for i in range(4):
        nr = row + dr[i]
        nc = col + dc[i]

        if not (1 <= nr < H - 1 and 1 <= nc < W - 1):
            continue

        if maze[nr][nc] == ".":
            continue

        candidates.append((nr, nc))

    if not candidates:
        stack.pop()
        continue

    nr, nc = random.choice(candidates)

    # 現在地と次のマスの間の壁を壊す
    wall_row = (row + nr) // 2
    wall_col = (col + nc) // 2

    maze[wall_row][wall_col] = "."
    maze[nr][nc] = "."

    stack.append((nr, nc))

# 通路からランダムにスタート・ゴールを選ぶ
roads = [
    (r, c)
    for r in range(H)
    for c in range(W)
    if maze[r][c] == "."
]

start_row, start_col = random.choice(roads)

goal_row, goal_col = random.choice(roads)
while (goal_row, goal_col) == (start_row, start_col):
    goal_row, goal_col = random.choice(roads)

print(H, W)
print(start_row, start_col)
print(goal_row, goal_col)

for row in maze:
    print("".join(row))
