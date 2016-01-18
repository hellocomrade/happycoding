#include "hashtable.h"
#ifdef _WIN32
static const char NEWLINE = '\r';
#else
static const char NEWLINE = '\n';
#endif
static const char NULCHAR = '\0';

static const int MAXERRMSG = 256;

static const int8_t SHIFT = 8;

struct _hash_node
{
	char *key;
	void *data;
	uint64_t datasize;
	struct _hash_node *next;
};
struct _hash_table
{
	struct _hash_node* bucks[NBUCKETS];
	uint64_t size;
};

static inline uint64_t hash(const char *key)
{
	uint64_t code = 0;
	while (NULCHAR != *(key) && NEWLINE != *(key))
		code = (code << SHIFT) + *(key++);
	return code % NBUCKETS;
}
static inline void delNode(struct _hash_node *pnode)
{
	if (pnode)
	{
		free(pnode->data);
		free(pnode->key);
		free(pnode);
	}
}
static inline struct _hash_node* createNode(const char * const key, const size_t keysize, void *data, const size_t datasize)
{
	struct _hash_node *pnode = (struct _hash_node*)malloc(sizeof(struct _hash_node));
	pnode->key = (char*)malloc(keysize + 1);
	pnode->next = NULL;
	strncpy(pnode->key, key, keysize);
	pnode->key[keysize] = NULCHAR;
	pnode->data = malloc(datasize);
	memcpy(pnode->data, data, datasize);
	pnode->datasize = datasize;
	return pnode;
}

struct _hash_table* createHashTab()
{
	struct _hash_table *ptab = (struct _hash_table*)malloc(sizeof(struct _hash_table));
	memset(ptab, 0, sizeof(struct _hash_table));
	return ptab;
}

int hashTabPut(struct _hash_table *table, const char * const key, size_t keysize, void *data, size_t datasize)
{
	if (!table || !key || keysize == 0 || !data || datasize == 0)
		return 10;
	uint64_t h = hash(key);
	struct _hash_node *prev = table->bucks[h], *curr = table->bucks[h];
	int ret;
	while (NULL != curr && (ret = strcmp(curr->key, key)) < 0)
	{
		prev = curr;
		curr = curr->next;
	}
	if (NULL != curr && 0 == ret)/*find a key conflict*/
	{
		free(curr->data);
		curr->data = malloc(datasize);
		memcpy(curr->data, data, datasize);
	}
	else
	{
		struct _hash_node *pnode = createNode(key, keysize, data, datasize);
		++table->size;
		if (NULL == curr)/*either we have reached the end of the list or there is currently no node in the bucket yet*/
		{
			if (NULL == prev)/*no node in this bucket yet*/
				table->bucks[h] = pnode;
			else
				prev->next = pnode;
		}
		else
		{
			if (curr == prev)/*key in pnode is smaller than the first node in the list*/
			{
				pnode->next = curr;
				table->bucks[h] = pnode;
			}
			else
			{
				prev->next = pnode;
				pnode->next = curr;
			}
		}
	}
	return 0;
}
void* hashTabLookup(struct _hash_table *table, const char * const key, size_t keysize, size_t *pdatasize, HASH_LOOKUP_MOD mod)
{
	void *data = NULL;
	if (NULL != table && NULL != pdatasize && NULL != key)
	{
		uint64_t h = hash(key);
		struct _hash_node *node, *prev;
		int ret;
		prev = node = table->bucks[h];
		while (NULL != node && (ret = strncmp(node->key, key, keysize)) < 0)
		{
			prev = node;
			node = node->next;
		}
		if (node != NULL && 0 == ret)
		{
			data = malloc(node->datasize);
			memcpy(data, node->data, node->datasize);
			*pdatasize = node->datasize;
			if (mod == REMOVE)
			{
				if (prev == node)
					table->bucks[h] = node->next;
				else
					prev->next = node->next;
				free(node);
				table->size--;
			}
		}
	}
	return data;
}
size_t gethashTabSize(struct _hash_table *table)
{
	return table->size;
}
void hashTabDestroy(struct _hash_table *table)
{
	if (table)
	{
		struct _hash_node *pnext, *pcurrent;
		int i = 0;
		for (; i<NBUCKETS; ++i)
		{
			pcurrent = table->bucks[i];
			while (pcurrent)
			{
				pnext = pcurrent->next;
				free(pcurrent->key);
				free(pcurrent->data);
				free(pcurrent);
				pcurrent = pnext;
			}
		}
		free(table);
	}
}
