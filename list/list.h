#pragma once
#include <cstddef>
using std::size_t;

template <typename T>
struct _listnode
{
	struct _listnode *next;
	T data;

	_listnode<T>() : next(nullptr), data(){}

	_listnode<T>(const T& t) : next(nullptr), data(t){}

	_listnode<T>& operator = (const _listnode<T>& l)
	{
		if (l == *this)return;
		this->next = l.next;
		this->data = l.data;
	}
};
//error C2823: a typedef template is illegal 
//template <typename T>
//typedef struct _listnode<T> ListNode;
//C11
template <typename T>
using ListNode = struct _listnode<T>;
/*
template<typename T>
ListNode<T>* BuildListFromArray(T *arr, size_t len);
template<typename T>
void CleanupList(ListNode<T> *phead);
*/
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
