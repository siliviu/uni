import time


def back_rec(l: list):
    sol = []
    cur = []
    l = sorted(l)

    def back_rec_util(mode=1):
        if len(cur) == len(l):
            sol.append([l[x] for x in cur])
            return
        for i, x in enumerate(l):
            if i not in cur and (len(cur) == 0 or mode == 1 or x <= l[cur[-1]]):
                cur.append(i)
                back_rec_util(mode & (not (len(cur) > 1 and mode == 1 and l[cur[-1]] < l[cur[-2]])))
                cur.pop()

    back_rec_util()
    return sol


def back_rec_fast(l: list):
    sol = []
    ind = []
    l = sorted(l)

    def back_rec_util(index=-1):
        for i in range(index+1, len(l)):
            if i == len(l)-1:
                sol.append([l[x] for x in ind] + [l[x] for x in range(i, -1, -1) if x not in ind])
            ind.append(i)
            back_rec_util(i)
            ind.pop()

    back_rec_util()

    return sol


def back_it(l: list):
    sol = []
    ind = [-1]
    l = sorted(l)
    n = len(l)
    while len(ind) > 0:
        ok = 0
        while ind[-1] < n:
            ind[-1] += 1
            if ind[-1] == n-1:
                sol.append([l[x] for x in ind] + [l[x] for x in range(n-1, -1, -1) if x not in ind])
                break
            ind.append(ind[-1])
            ok = 1
            break
        if not ok:
            ind.pop()
    return sol


a = [10, 27, 18, 16, 7, 14]
# a = [1, 2, 2, 3]
# a = [i for i in range(14)]

# st = time.time()

while True:
    option = int(input("Enter 1 for the recursive version and 2 for the iterative version:"))
    if option == 1:
     for x in back_rec_fast(a):
        print(x)
    else:
     for x in back_it(a):
        print(x)
    


# end = time.time()
# print(end-st)
