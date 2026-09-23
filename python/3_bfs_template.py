from collections import deque

# TODO を埋めるまでは実行してもエラーになります（それで正常です）

maze = [
    "........",
    ".####...",
    "....#...",
    ".##.....",
    "........",
]

H = len(maze)
W = len(maze[0])

sy, sx = 0, 0
gy, gx = 4, 7

# 各マスまでの距離。-1 は「まだ訪れていない」
dist = [[-1] * W for _ in range(H)]

dy = [-1, 1, 0, 0]
dx = [0, 0, -1, 1]

que = deque()

# スタート地点をキューに入れる
dist[sy][sx] = 0
que.append((sy, sx))

while que:
    # TODO 1:
    # キューの先頭から現在地を取り出そう


    for i in range(4):
        # TODO 2:
        # 次に移動する座標を求めよう


        # TODO 3:
        # 迷路の外ならスキップしよう


        # TODO 4:
        # 壁ならスキップしよう


        # TODO 5:
        # すでに訪問済みならスキップしよう


        # TODO 6:
        # 現在地から1手進んだ距離を記録しよう


        # TODO 7:
        # 次の場所をキューに追加しよう


answer = dist[gy][gx]

if answer == -1:
    print("ゴールには到達できません")
else:
    print("最短距離:", answer)
