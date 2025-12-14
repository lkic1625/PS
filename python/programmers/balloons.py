MAX = 1000000001

def solution(a):
    point, pivot = min((point, i) for (i, point) in enumerate(a))

    left = a[:pivot]
    right = a[pivot + 1:][::-1]

    answer = 0
    bef = MAX
    for point in left:
        if(bef > point):
            bef = point
            answer += 1

    bef = MAX
    for point in right:
        if(bef > point):
            bef = point
            answer += 1

    return answer + 1
