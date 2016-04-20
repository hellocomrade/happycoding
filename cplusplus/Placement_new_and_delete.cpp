#include <cstddef>
#include <new>
using namespace std;
/*
represent an internal implementation of the class details, which is encapsulated and only the pointer
is exposed to outsiders as a "handle".
But here, it's empty...
*/
class objInternal
{

};
class ObjectPublic
{
private:
	static const int POOL_SIZE = 32;
	static ObjectPublic* MemoryPool;
	/*
	We will need two pointers here: one for objInternal, after a specific ObjectPublic is initialized.
	The other one is for the memory list, which needs a pointer to the next block. The second pointer may
	seem to be unnecessary, since the memory for MemoryPool will be applied once as a whole. So, each block
	is actually side by side, in other words, they exist in continuous memory addresses.
	However, think about the case when the user call delete, where will you put the block back to free list?
	Head! So, after delete is called, the order of indexes in memory pool is gone. You will have to treat
	memory blocks as nodes on a list...

	To "save" the space for an extra 8 bytes, we use an union base upon the fact that these two pointers will
	never exist under the same context.
	*/
	union
	{
		objInternal *internal;
		ObjectPublic *next;
	};
public:
	static void* operator new (size_t size, new_handler handle = 0)
	{
		/*
		if required size is not equal to the size of ObjectPublic, our new operator can't handle
		it, pass it along to the default operator new defined in the global scope.
		*/
		if (size != sizeof(ObjectPublic))
		return ::operator new(size);
		ObjectPublic* ptr = MemoryPool;
		/*
		Does this look insane? Since the memory pool is organized as a list, there are two possible reasons
		that ptr could be equal to nullptr:
		1. Memory pool has not be initialized yet. OK, we will do it no problem;
		2. Memory pool has reached the end, no free memory anymore. We need to expand our memory pool.
		But, haven't you seen how it was implemented? It didn't try to keep tracking all allocated memory
		at all! We never track the head of the list and when a list runs out, we simply apply new memory!

		Is there a memory leak? Well, it will depend on the user! If users play nice and always remember calling
		delete after they are done, then we could be sure that all allocated memory blcok will be re-linked back
		to the memory pool, even they might not be applied at the same pool expansion.
		*/
		if (nullptr == ptr)
		{
			ptr = static_cast<ObjectPublic*>(::operator new(POOL_SIZE*sizeof(ObjectPublic)));
			for (int i = 0; i < POOL_SIZE - 1; ++i)
				ptr[i].next = ptr + i + 1;
			ptr[POOL_SIZE - 1].next = nullptr;
		}
		MemoryPool = ptr->next;
		return ptr;
	}
		/*
		Global ::operator delete only takes one argument, which is the pointer to the memory that needs to
		be destroyed. Why it doesn't need to know the size of the memory block? Well, ::operator new will leave
		info somewhere in the memory block it allocated (generally speaking, this info or cookie, is located couple
		bytes before the address that returns to the user), so delete can pick it up.
		For placement delete, since the implementation is unknow, we will need the second argument: size.
		*/
	static void operator delete (void *recycleObj, size_t size)
	{
		if (nullptr == recycleObj)return;
		if (size != sizeof(ObjectPublic))
			return ::operator delete(recycleObj);
		ObjectPublic *phead = static_cast<ObjectPublic*>(recycleObj);
		/*
		Simply put the returned block to the head of the list.
		*/
		phead->next = MemoryPool;
		MemoryPool = phead;
	}
};
ObjectPublic* ObjectPublic::MemoryPool = nullptr;

void testPlacementNewDelete()
{
	ObjectPublic *pObj = new ObjectPublic;
	delete pObj;
}
