#include "list.h"
#include "util.h"


/// <summary>
/// Adds a transaction
/// </summary>
/// <param name="l">account to add to</param>
/// <param name="day">day of the transaction</param>
/// <param name="sum">transaction sum</param>
/// <param name="type">transaction type</param>
/// <param name="desc">description of transaction</param>
/// <returns>1 if successful, 0 otherwise</returns>
int AddTransaction(List* l, int day, int sum, TransactionType type, char* desc);

/// <summary>
/// Modifies a transaction
/// </summary>
/// <param name="l">account to add to</param>
/// <param name="day">day of the transaction</param>
/// <param name="sum">transaction sum</param>
/// <param name="type">transaction type</param>
/// <param name="desc">description of transaction</param>
/// <returns>1 if successful, 0 otherwise</returns>
int ModifyTransaction(List* l, int pos, int day, int sum, TransactionType type, char* desc);

/// <summary>
/// Removes a transaction
/// </summary>
/// <param name="l">account to remove from</param>
/// <param name="pos">which transaction to remove</param>
/// <returns>1 if successful, 0 otherwise</returns>
int RemoveTransaction(List* l, int pos);

/// <summary>
/// Get a transaction
/// </summary>
/// <param name="l">account</param>
/// <param name="pos">which transaction</param>
/// <returns>pointer to transaction</returns>
Transaction* GetTransaction(List* l, int pos);

/// <summary>
/// Counts the number of transactions
/// </summary>
/// <param name="l">account</param>
/// <returns>number of transactions</returns>
int CountTransactions(List* l);

/// <summary>
/// Filter transactions by a type
/// </summary>
/// <param name="l">account</param>
/// <param name="type">Filter Type Enum</param>
/// <param name="sum">parameter for filter if type is 2,3</param>
/// <returns>a new account (copy) with the transactions filtered</returns>

List FilterTransactions(List* l, FilterType type, int sum);

/// <summary>
/// Order transactions
/// </summary>
/// <param name="l">account</param>
/// <param name="type">Order Type Enum</param>
/// <returns>a new account (copy) with the transactions ordered</returns>
List OrderTransactions(List* l, OrderType type);