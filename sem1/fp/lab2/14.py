def isperfect(x):
    s = 0
    for i in range(1, x):
        if x % i == 0:
            s += i
    return s == x


n = int(input())
n += 1

while not isperfect(n):
    n += 1

print(n)
