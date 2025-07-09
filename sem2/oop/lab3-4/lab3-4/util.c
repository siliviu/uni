#include "util.h"

void ssort(void* v, size_t num, size_t size, int comp(void const*, void const*)) {
	void* temp = malloc(size);
	for (int i = 0; i < num; ++i) {
		void* vi = (void*)((char*)v + (i * size) / sizeof(char));
		for (int j = i + 1; j < num; ++j) {
			void* vj = (void*)((char*)v + (j * size) / sizeof(char));
			if (comp(vj, vi) < 0) {
				memcpy(temp, vi, size);
				memcpy(vi, vj, size);
				memcpy(vj, temp, size);
			}
		}
	}
	free(temp);
}

int orderincsum(const void* a, const void* b) {
	return ((Transaction*)a)->sum - ((Transaction*)b)->sum;
}

int orderdecsum(const void* a, const void* b) {
	return ((Transaction*)b)->sum - ((Transaction*)a)->sum;
}

int orderincday(const void* a, const void* b) {
	return ((Transaction*)a)->day - ((Transaction*)b)->day;
}

int orderdecday(const void* a, const void* b) {
	return ((Transaction*)b)->day - ((Transaction*)a)->day;
}