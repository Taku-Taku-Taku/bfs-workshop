# 迷路で学ぶ探索アルゴリズム入門

## 0. 今日のゴール

今日は、迷路探索を題材に **幅優先探索（BFS）** を学びます。

最終的には、次の3つをできるようにします。

1. スタートからゴールへ到達できるか調べる
2. ゴールまでの最短距離を求める
3. ゴールまでの最短経路を復元する

使用する迷路は次の形式です。

```text
5 8
0 0
4 7
........
.####...
....#...
.##.....
........
```

- 1行目: 高さ `H` と幅 `W`
- 2行目: スタート地点 `start_row start_col`
- 3行目: ゴール地点 `goal_row goal_col`
- `.`: 通れるマス
- `#`: 壁

座標は **0始まり** です。
上下左右の4方向に動けて、1回の移動を1手と数えます。

---

## 0.1 使うファイルと実行方法

ファイル名の先頭の番号は、**使う順番**です。上から順に進みます。

| 順 | 場面 | Python | C++ |
|---|---|---|---|
| 0 | スタックの例 | `python/0_stack_sample.py` | `cpp/0_stack_sample.cpp` |
| 1 | キューの例 | `python/1_queue_sample.py` | `cpp/1_queue_sample.cpp` |
| 2 | ミニ演習 | `python/2_stack_queue_exercise.py` | `cpp/2_stack_queue_exercise.cpp` |
| 3 | **BFS穴埋め（メイン）** | `python/3_bfs_template.py` | `cpp/3_bfs_template.cpp` |
| 4 | 別の迷路で試す | `python/4_bfs_from_file.py` | `cpp/4_bfs_from_file.cpp` |
| 5 | 迷路の自動生成（おまけ） | `python/5_maze_generator.py` | `cpp/5_maze_generator.cpp` |

解答は `answers/` フォルダにまとめてあります。番号は対応する教材と同じです。

| 順 | 内容 | Python | C++ |
|---|---|---|---|
| 2 | ミニ演習の解答 | `python/answers/2_stack_queue_answer.py` | `cpp/answers/2_stack_queue_answer.cpp` |
| 3 | BFSの解答 | `python/answers/3_bfs_answer.py` | `cpp/answers/3_bfs_answer.cpp` |
| 3 | 最短経路つきの完成版 | `python/answers/3_bfs_path_answer.py` | `cpp/answers/3_bfs_path_answer.cpp` |

実行方法:

```text
# Python
cd python
python3 3_bfs_template.py

# C++（-std=c++17 を必ず付ける）
cd cpp
g++ -std=c++17 -o 3_bfs_template 3_bfs_template.cpp
./3_bfs_template
```

Windows では `python3` を `python`、`./3_bfs_template` を `3_bfs_template.exe` に読み替えてください。

---

# 1. スタックとキュー

## スタック

スタックは、**最後に入れたものから取り出す**データ構造です。

```text
push 1
push 2
push 3

[1, 2, 3]
       ↑
     ここから取り出す
```

取り出す順番:

```text
3 → 2 → 1
```

### C++

```cpp
#include <iostream>
#include <stack>
using namespace std;

int main() {
    stack<int> st;

    st.push(1);
    st.push(2);
    st.push(3);

    while (!st.empty()) {
        cout << st.top() << '\n';
        st.pop();
    }
}
```

### Python

```python
st = []

st.append(1)
st.append(2)
st.append(3)

while st:
    print(st.pop())
```

---

## キュー

キューは、**最初に入れたものから取り出す**データ構造です。

```text
push 1
push 2
push 3

[1, 2, 3]
 ↑
ここから取り出す
```

取り出す順番:

```text
1 → 2 → 3
```

### C++

```cpp
#include <iostream>
#include <queue>
using namespace std;

int main() {
    queue<int> que;

    que.push(1);
    que.push(2);
    que.push(3);

    while (!que.empty()) {
        cout << que.front() << '\n';
        que.pop();
    }
}
```

### Python

```python
from collections import deque

que = deque()

que.append(1)
que.append(2)
que.append(3)

while que:
    print(que.popleft())
```

---

## 練習問題

次の値を順番に追加してください。

```text
10
20
30
40
```

### 問題1

スタックを使って次のように出力してください。

```text
40
30
20
10
```

### 問題2

キューを使って次のように出力してください。

```text
10
20
30
40
```

---

# 2. 幅優先探索（BFS）

迷路のスタート地点から、**近いマスから順番に調べる**ことを考えます。

例えばスタート地点を `(0, 0)` とすると、

```text
  0 1 2 3
0 S . . .
1 . # . .
2 . . . G
```

スタートから近い順に調べると、

```text
  0 1 2 3
0 0 1 2 3
1 1 # 3 4
2 2 3 4 5
```

のように距離が広がります。

このとき、**次に調べるマスをキューに入れて管理**します。

キューは「先に入れたものから出る」ので、スタートに近いマスから順番に処理されます。
そのため、**あるマスに最初に到達したときの距離が、そのマスへの最短距離**になります。

だからこそ、**一度訪れたマスは二度と調べません**。
あとから来た経路は、必ず最初の経路より遠回りだからです。

---

## BFSの基本手順

1. スタート地点をキューに入れる
2. キューの先頭を取り出す
3. 上下左右を確認する
4. 行けるマスなら距離を記録してキューに入れる
5. キューが空になるまで繰り返す

疑似コード:

```text
スタートをキューに入れる

while キューが空ではない:
    現在地をキューから取り出す

    上下左右について:
        次の場所を求める

        迷路の外ならスキップ
        壁ならスキップ
        すでに訪問済みならスキップ

        距離を記録する
        キューに追加する
```

---

# 3. 上下左右への移動

上下左右は次のように表します。

| 方向 | rowの変化 | colの変化 |
|---|---:|---:|
| 上 | -1 | 0 |
| 下 | +1 | 0 |
| 左 | 0 | -1 |
| 右 | 0 | +1 |

C++:

```cpp
int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};
```

Python:

```python
dr = [-1, 1, 0, 0]
dc = [0, 0, -1, 1]
```

`i` 番目の方向に進んだ先は `(row + dr[i], col + dc[i])` です。

## 迷路の外に出ていないか確認する

移動した先が迷路の外になることがあります。
**壁かどうかを調べる前に**、迷路の中にあるか確認します。

Python:

```python
if not (0 <= next_row < H and 0 <= next_col < W):
    continue
```

C++:

```cpp
if (next_row < 0 || next_row >= H || next_col < 0 || next_col >= W) {
    continue;
}
```

## キューに座標を入れる

キューに入れるのは「行と列」の2つの値の組です。

Python:

```python
que.append((row, col))       # 追加
row, col = que.popleft()     # 先頭を取り出す
```

C++:

```cpp
queue<pair<int, int>> que;

que.push({row, col});             // 追加

auto [row, col] = que.front();    // 先頭を見る（row と col に分けて受け取る）
que.pop();                        // 先頭を削除
```

---

# 4. BFSを実装してみよう

`3_bfs_template.py` / `3_bfs_template.cpp` の TODO を埋めます。

まずは、スタートから各マスまでの最短距離を求めます。

`dist[row][col]` に、

- `-1`: まだ訪れていない
- `0以上`: スタートからの距離

を保存します。

この `dist` が「訪問済みかどうか」の記録も兼ねています。

## 穴埋めのポイント

BFSの中心になる部分は次の通りです。

```text
while キューが空ではない:
    現在地を取り出す

    for 上下左右:
        次の座標を求める

        if 迷路の外:
            continue

        if 壁:
            continue

        if 訪問済み:
            continue

        次の場所の距離 = 現在地の距離 + 1
        次の場所をキューに追加
```

TODO を埋めるまではプログラムは正しく動きません。
（Pythonはエラー、C++は無限ループになります。止まらないときは `Ctrl + C`）

---

# 5. 最短距離

BFSが終了したら、

```text
dist[goal_row][goal_col]
```

を確認します。

- `-1` のまま → 到達できない
- `0以上` → その値が最短距離

到達できない迷路でも、キューが空になればBFSは必ず止まります。
特別な処理は要りません。

## ゴールを見つけた時点で止めてもよい？

止めて大丈夫です。
BFSは距離の小さい順に処理し、一度入れた距離を書き換えないので、
**ゴールに数字が入った瞬間、それがもう最短距離**です。

今回のコードは、全マスの距離を求める一番簡単な形にしています。
ゴールまでの距離だけが必要なら、見つけた時点で打ち切れます。

ただし、**到達できないことを確かめるには最後まで回す**必要があります。

---

# 6. 最短経路を復元する

最短距離だけでなく、どの道を通ったかも求めてみます。

各マスについて、

```text
どこからこのマスへ来たか
```

を保存します。`dist` と同じ形の表をもう2つ用意して、

```text
prev_row[next_row][next_col] = row
prev_col[next_row][next_col] = col
```

と記録しておきます。

ゴールから逆にたどると、

```text
Goal
 ↑
 ○
 ↑
 ○
 ↑
Start
```

のように最短経路を復元できます。

```text
row, col = ゴール

while (row, col) がスタートでない:
    (row, col) に印をつける
    (row, col) = (prev_row[row][col], prev_col[row][col])
```

動くものは `answers/3_bfs_path_answer.py` / `answers/3_bfs_path_answer.cpp` にあります。

---

# 7. 別の迷路で試す

`mazes/` フォルダに迷路ファイルがあります。

- `4_bfs_from_file.py` / `4_bfs_from_file.cpp` の `maze_file` を書き換えると、その迷路で試せます。
- 自分で書いたプログラムで試すときは、`maze` の中身と `start_row` などを書き換えます。

例: 到達できない迷路 `maze05_unreachable.txt`

```python
maze = [
    ".......",
    "#######",
    ".......",
    "#######",
    ".......",
]

start_row, start_col = 0, 0
goal_row, goal_col = 4, 6
```

「ゴールには到達できません」と表示されれば正解です。

`maze11_detour.txt` は、大きく遠回りしないとゴールに行けない迷路です。
まっすぐ進めば14手に見えますが、最短距離は30手です。

---

# 8. DFSについて

BFSと似た探索方法に **DFS（深さ優先探索）** があります。

- BFS: 近いところから順番に探索
- DFS: 行けるところまで深く進んでから戻る

典型的には、

- BFS → キュー
- DFS → スタック / 再帰

を使います。

DFSでも「ゴールに到達できるか」は調べられます。
ただし、先に見つかった経路が最短とは限りません。
最短距離を求めたい今回は、BFSを使います。

---

# 9. 最後に

今日の重要ポイントは3つです。

- BFSでは **キュー** を使う
- 近い場所から順番に探索する
- 同じ場所を何度も調べない

迷路以外にも、

- ゲームマップ
- SNSのつながり
- ネットワーク
- グラフ

など、さまざまな問題に同じ考え方を使えます。

---

# おまけ: 迷路を自動生成する

`python/5_maze_generator.py` または `cpp/5_maze_generator.cpp` では、
迷路そのものをランダムに生成できます。

この生成処理は **スタックを使ったDFS（深く進み、行き止まりで戻る）** です。

ただし、これは今回のBFS本編では扱いません。
時間が余った場合のデモ用です。

生成結果は、BFS教材と同じ形式です。

```text
H W
start_row start_col
goal_row goal_col
迷路...
```

そのため、ファイルに保存すればそのままBFSの入力として使えます。

```text
cd python
python3 5_maze_generator.py > ../mazes/generated.txt
```
