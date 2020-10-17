import sys
input = sys.stdin.readline
print = sys.stdout.write

# input
N, K = map(int, input().split())
DP = {0:0} # weight : value
for _ in range(N):
    # input
    W, V = map(int, input().split())
    item = {}
    for weight, value in DP.items():
        if W + weight <= K and DP.get(W + weight, 0) < V + value:
            item[W + weight] = V + value
    DP.update(item)
print(f'{max(DP.values())}')