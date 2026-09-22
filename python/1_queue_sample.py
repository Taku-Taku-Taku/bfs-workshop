from collections import deque

que = deque()

que.append(1)
que.append(2)
que.append(3)

while que:
    print(que.popleft())
