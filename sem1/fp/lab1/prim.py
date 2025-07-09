a = int(input())


def isprime(a):
    if a < 2 or (a > 2 and a % 2 == 0):
        return "No"
    p = 3
    while p * p <= a:
        if a % p == 0:
            return "No"
        p += 2
    return "Yes"


print(isprime(a))
