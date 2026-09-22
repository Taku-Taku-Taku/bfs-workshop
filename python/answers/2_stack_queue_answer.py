from collections import deque

# 問題1: stack
st = []

st.append(10)
st.append(20)
st.append(30)
st.append(40)

while st:
    print(st.pop())

print("-----")

# 問題2: queue
que = deque()

que.append(10)
que.append(20)
que.append(30)
que.append(40)

while que:
    print(que.popleft())
