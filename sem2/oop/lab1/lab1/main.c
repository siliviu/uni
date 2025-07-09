#include <stdio.h>

int main() {
	printf("Enter how many numbers you wish to read: ");
	int n;
	scanf("%d", &n);
	int s = 0;
	while (n--) {
		int x;
		scanf("%d", &x);
		s += x;
	}
	printf("Their sum is: %d", s);
}