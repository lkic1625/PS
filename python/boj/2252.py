import sys
from collections import deque
input = sys.stdin.readline

max_n, max_m = 32000 + 1, 100000 + 1
indegree = [0]*(max_n + 1)
adj = [deque() for _ in range(max_n + 1)]
#queue for bfs
queue = deque()

# input
n, m = map(int, input().split())
for _ in range(m):

    a, b = map(int, input().split())
    # a -> b
    indegree[b] += 1
    # update adj list
    adj[a].append(b)

#push to the queue if indegree == 0
for node in range(n):
    if indegree[node] == 0:
        queue.append(node)

while queue:
    vertex = queue.pop()
    # print sorted sequence
    print(vertex)
    while adj[vertex]:
        child = adj[vertex].pop()
        # update child node's indegree
        indegree[child] -= 1
        # push to the queue when node's indegree == 0
        if(indegree[child] == 0):
            queue.append(child)

