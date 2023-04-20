#pragma once
#include "transaction.h"

typedef enum { TYPEIN, TYPEOUT, LESSSUM, GREATERSUM } FilterType;

typedef enum { INCSUM, DECSUM, INCDAY, DECDAY} OrderType;

/// <summary>
/// Sorts an array in place in O(N^2), using selection sort. Same arguments as qsort
/// </summary>
/// <param name="v">array</param>
/// <param name="num">number of elements in array</param>
/// <param name="size">size of an element</param>
/// <param name="comp">comparator function</param>
void ssort(void* v, size_t num, size_t size, int comp(void const*, void const*));

// Comparator to order transactions by sum in increasing order
int orderincsum(const void* a, const void* b);

// Comparator to order transactions by sum in decreasing order
int orderdecsum(const void* a, const void* b);

// Comparator to order transactions by day in increasing order
int orderincday(const void* a, const void* b);

// Comparator to order transactions by day in decreasing order
int orderdecday(const void* a, const void* b);