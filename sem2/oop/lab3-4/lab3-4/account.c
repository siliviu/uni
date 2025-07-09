#include "account.h"

int AddTransaction(List* l, int day, int sum, TransactionType type, char* desc) {
	if (!ValidateTransaction(day, sum, type, desc))
		return 0;
	Transaction t = CreateTransaction(day, sum, type, desc);
	AddListTransaction(l, t);
	return 1;
}

int ModifyTransaction(List* l, int pos, int day, int sum, TransactionType type, char* desc) {
	if (!ValidatePosition(l, pos) || !ValidateTransaction(day, sum, type, desc))
		return 0;
	Transaction t = CreateTransaction(day, sum, type, desc);
	ModifyListTransaction(l, pos, t);
	return 1;
}

int RemoveTransaction(List* l, int pos) {
	if (!ValidatePosition(l, pos))
		return 0;
	DeleteListTransaction(l, pos);
	return 1;
}

Transaction* GetTransaction(List* l, int pos) {
	return GetListElement(l, pos);
}

int CountTransactions(List* l) {
	return GetListLength(l);
}

List FilterTransactions(List* l, FilterType type, int sum) {
	List r = CreateList();
	int n = CountTransactions(l);
	for (int i = 0; i < n; ++i) {
		Transaction* t = GetTransaction(l, i);
		if ((type == TYPEIN && t->type == IN) ||
			(type == TYPEOUT && t->type == OUT) ||
			(type == LESSSUM && t->sum < sum) ||
			(type == GREATERSUM && t->sum > sum))
			AddListTransaction(&r, CopyTransaction(t));
	}
	return r;
}

List OrderTransactions(List* l, OrderType type) {
	List r = CopyList(l);
	ssort(r.v, CountTransactions(&r), sizeof(Transaction),
		type == INCSUM ? orderincsum :
		type == DECSUM ? orderdecsum :
		type == INCDAY ? orderincday :
		orderdecday
	);
	return r;
}