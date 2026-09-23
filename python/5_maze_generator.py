import random

# 奇数サイズを推奨
H = 21
W = 31

if H % 2 == 0 or W % 2 == 0:
    raise ValueError("H, W は奇数にしてください")

maze = [["#"] * W for _ in range(H)]

# 1マス飛ばしで進み、間の壁も壊す
dy = [-2, 2, 0, 0]
dx = [0, 0, -2, 2]

stack = [(1, 1)]
maze[1][1] = "."

while stack:
    y, x = stack[-1]

    candidates = []

    for i in range(4):
        ny = y + dy[i]
        nx = x + dx[i]

        if not (1 <= ny < H - 1 and 1 <= nx < W - 1):
            continue

        if maze[ny][nx] == ".":
            continue

        candidates.append((ny, nx))

    if not candidates:
        stack.pop()
        continue

    ny, nx = random.choice(candidates)

    # 現在地と次のマスの間の壁を壊す
    wy = (y + ny) // 2
    wx = (x + nx) // 2

    maze[wy][wx] = "."
    maze[ny][nx] = "."

    stack.append((ny, nx))

# 通路からランダムにスタート・ゴールを選ぶ
roads = [
    (y, x)
    for y in range(H)
    for x in range(W)
    if maze[y][x] == "."
]

sy, sx = random.choice(roads)

gy, gx = random.choice(roads)
while (gy, gx) == (sy, sx):
    gy, gx = random.choice(roads)

maze[sy][sx] = "S"
maze[gy][gx] = "G"

print(H, W)
print(sy, sx)
print(gy, gx)

for line in maze:
    print("".join(line))
