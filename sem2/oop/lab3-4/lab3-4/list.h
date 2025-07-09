#include "transaction.h"

typedef struct {
	Transaction *v;
	int capacity, length;
} List;

/// <summary>
/// Creates an empty list
/// </summary>
/// <returns>Returns a new list</returns>
List CreateList();

/// <summary>
/// Adds a transaction to a list
/// </summary>
/// <param name="l">list to add to</param>
/// <param name="e">element to add</param>
void AddListTransaction(List* l, Transaction e);

/// <summary>
/// Modifies the element of a list (indexed from 0)
/// </summary>
/// <param name="l">list to modify</param>
/// <param name="pos">position to modify at</param>
/// <param name="e">new element</param>
void ModifyListTransaction(List* l, int pos, Transaction e);

/// <summary>
/// Deletes a transaction from a list (indexed from 0)
/// </summary>
/// <param name="l">list to delete from</param>
/// <param name="pos">position to delete</param>
void DeleteListTransaction(List* l, int pos);

/// <summary>
/// Get a reference to a list element (indexed from 0)
/// </summary>
/// <param name="l">list</param>
/// <param name="pos">position of the element</param>
/// <returns>pointer to the element</returns>
Transaction* GetListElement(List* l, int pos);

/// <summary>
/// Gets the length of a list
/// </summary>
/// <param name="l">list</param>
/// <returns>length of list</returns>
int GetListLength(List* l);

/// <summary>
/// Validates if index is valid in a list (indexed from 0)
/// </summary>
/// <param name="l"></param>
/// <param name="pos"></param>
/// <returns>true/false</returns>
int ValidatePosition(List* l, int pos);

/// <summary>
/// Deletes list
/// </summary>
/// <param name="l"></param>
void DeleteList(List* l);

/// <summary>
/// Copies a list
/// </summary>
/// <param name="l"></param>
/// <returns>copy of list</returns>
List CopyList(List* l);