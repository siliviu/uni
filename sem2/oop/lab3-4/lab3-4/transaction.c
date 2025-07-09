#include "transaction.h"

int ValidateTransaction(int day, int sum, TransactionType type, char* desc) {
	if (day < 1 || day > 31)
		return 0;
	if (sum < 0)
		return 0;
	if (type != IN && type != OUT)
		return 0;
	return strlen(desc) != 0;
}

Transaction CreateTransaction(int day, int sum, TransactionType type, char* desc) {
	Transaction a = { day,sum,type };
	a.desc = (char*)malloc(sizeof(char) * (strlen(desc) + 1));
	strcpy(a.desc, desc);
	return a;
}


Transaction CopyTransaction(Transaction* t) {
	return CreateTransaction(t->day, t->sum, t->type, t->desc);
}

void DeleteTransaction(Transaction* t) {
	free(t->desc);
}