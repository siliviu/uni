from termcolor import colored

x = "0"


def gcd(a, b):
    if b == 0:
        return a
    return gcd(b, a % b)


def isprime(a):
    if a < 2 or (a > 2 and a % 2 == 0):
        return False
    p = 3
    while p * p <= a:
        if a % p == 0:
            return False
        p += 2
    return True


def solve_2(array):
    m = len(array)
    for i in range(m - 1):
        if gcd(array[i], array[i + 1]) != 1:
            return False
    return True


def solve_3(array):
    for i in array:
        if not isprime(i):
            return False
    return True


# def solve_12(array):
#     m = len(array)
#     for i in range(m - 1):
#         if array[i] * array[i + 1] > 0:
#             return False
#     return True


def findseq(func, arr):
    lenmax = 0
    ans = []
    n = len(arr)
    for i in range(0, n):
        for j in range(i, n):
            if func(arr[i : j + 1]) == True and j - i + 1 > lenmax:
                ans = arr[i : j + 1]
                lenmax = j - i + 1
    return ans


def test_2():
    assert findseq(solve_2, [2, 3, 5, 4, 3]) == [2, 3, 5, 4, 3]
    assert findseq(solve_2, [2, 5, 2, 2]) == [2, 5, 2]
    assert findseq(solve_2, [2, 3, 5, 8, 9, 6]) == [2, 3, 5, 8, 9]
    assert findseq(solve_2, []) == []


def print_menu():
    print(
        """
Press 1 to enter a list on a single line, separated with spaces
Press 2 to find the longest list where all adjacent numbers are coprime
Press 3 to find the longest list where all numbers are prime
Press 4 to exit
"""
    )

test_2()

print(
    """Welcome! 
Choose one of the commands below by typing the corresponding number and hitting enter:
    """
)

a = []

while x != "4":
    print_menu()
    x = input()
    if x == "1":
        try:
            a = list(map(int, input().split()))
            print("The list is now", end=" ")
        except:
            print("You have entered a bad list. The list remains", end=" ")
        print(colored(a, "blue"))
    elif x == "2":
        print("The list is:", colored(findseq(solve_2, a), "blue"))
    elif x == "3":
        print("The list is:", colored(findseq(solve_3, a), "blue"))
    # elif x == "12":
        # print("The list is:", colored(findseq(solve_12, a), "blue"))
    elif x != "4":
        print("Option does not exist, please try again")

print("Goodbye!")
