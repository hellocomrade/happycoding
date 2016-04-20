#include "list.h"
template<typename T>
ListNode<T>* BuildListFromArray(T *arr, size_t len)
{
	size_t i = 1;
	ListNode<T> *phead = new ListNode<T>();
	phead->data = arr[0];
	ListNode<T> *itor = phead;
	for (; i < len; ++i)
	{
		itor->next = new ListNode<T>();
		itor->next->data = arr[i];
		itor = itor->next;
	}
	return phead;
}
template<typename T>
void CleanupList(ListNode<T> *phead)
{
	ListNode<T> *itor = nullptr;
	while (phead != nullptr)
	{
		itor = phead;
		phead = phead->next;
		delete itor;
	}
}
