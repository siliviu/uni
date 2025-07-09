#pragma once
#include <stdlib.h>
#include <string.h>

typedef enum { IN, OUT } TransactionType;


typedef struct {
	int day, sum, type;
	char* desc;
} Transaction;

/// <summary>
/// Validates data for a possible transaction
///  </summary>
/// <param name="day"></param>
/// <param name="sum"></param>
/// <param name="type"></param>
/// <param name="desc"></param>
/// <returns>1 if valid, 0 otherwise</returns>
int ValidateTransaction(int day, int sum, TransactionType type, char* desc);

/// <summary>
/// Constructor for transaction struct
/// </summary>
/// <param name="day"></param>
/// <param name="sum"></param>
/// <param name="type">in/out</param>
/// <param name="desc">a short description</param>
/// <returns>transaction struct</returns>
Transaction CreateTransaction(int day, int sum, TransactionType type, char* desc);


/// <summary>
/// Deletes a transaction
/// </summary>
/// <param name="t">transaction</param>
void DeleteTransaction(Transaction* t);

/// <summary>
/// Returns a copy of the transaction
/// </summary>
/// <param name="t"></param>
/// <returns></returns>
Transaction CopyTransaction(Transaction* t);