#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Calculates the square root of a number with 1e-11 precisions.
* x - long double - must be a positive number
Returns - long double - the square root of the number, also a positive number
*/
long double get_root(long double x) {
	long double left = 0, right = 1e11;
	while (right - left > 1e-11) {
		long double m = (left + right) / 2;
		if (m * m > x)
			right = m;
		else
			left = m;
	}
	return left;
}

// Function for the first problem
void run_1() {
	printf("Enter the number you wish to find the square root: ");
	long double x;
	(void)scanf("%Lf", &x);
	printf("Enter the precision: ");
	int p;
	(void)scanf("%d", &p);
	char format[10];
	sprintf(format, "%%0.%dLf\n", p);
	long double nr = get_root(x);
	if (nr == 0)
		printf("The number must be positive!\n");
	else
		printf(format, nr);
}

// Function for the second problem. O(n log log n)
void run_2() {
	printf("Enter the number up to which you wish to generate prime numbers: ");
	int n;
	(void)scanf("%d", &n);
	if (n < 2) {
		printf("No prime numbers\n");
		return;
	}
	char* sieve = (char*)(malloc(n * sizeof(char)));
	memset(sieve, 0, n * sizeof(char));
	for (int i = 3; i * i <= n; i += 2)
		if (!sieve[i])
			for (int j = i * i; j <= n; j += 2 * i)
				sieve[j] = 1;
	printf("The prime numbers are:\n2 ");
	for (int i = 3; i <= n; i += 2)
		if (!sieve[i])
			printf("%d ", i);
	printf("\n");
	free(sieve);
}

// Main function
int main() {
	printf("Welcome!\n");
	while (1) {
		printf("Enter 1 for problem 7.\nEnter 2 for problem 1.\nEnter anything else to exit.\n");
		int x;
		(void)scanf("%d", &x);
		if (x == 1)
			run_1();
		else if (x == 2)
			run_2();
		else
			break;
	}
	printf("Goodbye!");
}