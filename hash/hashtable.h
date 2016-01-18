#ifndef HAPPY_CODING_HASH_H
#define HAPPY_CODING_HASH_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define NBUCKETS 31

#ifdef __cplusplus
extern "C"{
#endif

	struct _hash_table;
	typedef struct _hash_table* HASHTAB;
	typedef enum{
		KEEP,
		REMOVE
	}HASH_LOOKUP_MOD;

	static inline uint64_t hash(const char *key);
	struct _hash_table* createHashTab();
	int hashTabPut(struct _hash_table *table, const char * const key, size_t keysize, void *data, size_t datasize);
	void* hashTabLookup(struct _hash_table *table, const char * const key, size_t keysize, size_t *pdatasize, HASH_LOOKUP_MOD mod);
	void hashTabDestroy(struct _hash_table *table);
	size_t gethashTabSize(struct _hash_table *table);
	
#ifdef __cplusplus
}
#endif

#endif // HAPPY_CODING_HASH_H

