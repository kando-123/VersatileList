#include "list.h"

#define FAILURE (!SUCCESS)

Iterator_T ListIterator_Front(List_S* list)
{
	return list ? list->head : NULL;
}

Iterator_T ListIterator_Back(List_S* list)
{
	return list ? list->tail : NULL;
}

Iterator_T ListIterator_At(List_S* list, pos_t position)
{
	if (!list)
	{
		return NULL;
	}
	
	if (position >= 0 && position < list->size)
	{
		Node_S* node = list->head;
		for (pos_t i = 0; node && i < position; ++i)
		{
			node = node->next;
		}
		return node;
	}
	else if (position < 0 && position >= -list->size)
	{
		Node_S* node = list->tail;
		for (pos_t i = -1; node && i > position; --i)
		{
			node = node->prev;
		}
		return node;
	}
	
	return NULL;
}

Iterator_T ListIterator_FirstEqual(List_S* list, const Object_S* object)
{
	if (!list || !object)
	{
		return NULL;
	}

	for (Node_S* node = list->head; node; node = node->next)
	{
		if (Object_Equal(&node->data, object))
		{
			return node;
		}
	}

	return NULL;
}

Iterator_T ListIterator_LastEqual(List_S* list, const Object_S* object)
{
	if (!list || !object)
	{
		return NULL;
	}

	for (Node_S* node = list->tail; node; node = node->prev)
	{
		if (Object_Equal(&node->data, object))
		{
			return node;
		}
	}

	return NULL;
}

Iterator_T ListIterator_FirstIf(List_S* list, UnaryPredicate_F predicate)
{
	if (!list || !predicate)
	{
		return NULL;
	}

	for (Node_S* node = list->head; node; node = node->next)
	{
		if ((*predicate)(&node->data))
		{
			return node;
		}
	}

	return NULL;
}

Iterator_T ListIterator_LastIf(List_S* list, UnaryPredicate_F predicate)
{
	if (!list || !predicate)
	{
		return NULL;
	}

	for (Node_S* node = list->tail; node; node = node->prev)
	{
		if ((*predicate)(&node->data))
		{
			return node;
		}
	}

	return NULL;
}

Iterator_T ListIterator_Next(Iterator_T iterator)
{
	return iterator ? iterator->next : NULL;
}

Iterator_T ListIterator_Previous(Iterator_T iterator)
{
	return iterator ? iterator->prev : NULL;
}

Iterator_T ListIterator_Advance(Iterator_T iterator, pos_t offset)
{
	if (!iterator)
	{
		return NULL;
	}

	if (offset > 0)
	{
		for (pos_t i = 0; iterator && i < offset; ++i)
		{
			iterator = iterator->next;
		}
	}
	else if (offset < 0)
	{
		for (pos_t i = 0; iterator && i > offset; --i)
		{
			iterator = iterator->prev;
		}
	}

	return iterator;
}

Iterator_T ListIterator_NextEqual(Iterator_T iterator, const Object_S* object)
{
	if (!iterator || !object)
	{
		return NULL;
	}

	do
	{
		iterator = iterator->next;
	}
	while (!Object_Equal(&iterator->data, object));

	return iterator;
}

Iterator_T ListIterator_PreviousEqual(Iterator_T iterator, const Object_S* object)
{
	if (!iterator || !object)
	{
		return NULL;
	}

	do
	{
		iterator = iterator->prev;
	}
	while (!Object_Equal(&iterator->data, object));

	return iterator;
}

Iterator_T ListIterator_NextSame(Iterator_T iterator)
{
	if (!iterator)
	{
		return NULL;
	}

	Object_S* object = &iterator->data;
	do
	{
		iterator = iterator->next;
	}
	while (!Object_Equal(&iterator->data, object));

	return iterator;
}

Iterator_T ListIterator_PreviousSame(Iterator_T iterator)
{
	if (!iterator)
	{
		return NULL;
	}

	Object_S* object = &iterator->data;
	do
	{
		iterator = iterator->prev;
	}
	while (!Object_Equal(&iterator->data, object));

	return iterator;
}

Iterator_T ListIterator_NextIf(Iterator_T iterator, UnaryPredicate_F predicate)
{
	if (!iterator || !predicate)
	{
		return NULL;
	}

	do
	{
		iterator = iterator->next;
	}
	while (!(*predicate)(&iterator->data));

	return iterator;
}

Iterator_T ListIterator_PreviousIf(Iterator_T iterator, UnaryPredicate_F predicate)
{
	if (!iterator || !predicate)
	{
		return NULL;
	}

	do
	{
		iterator = iterator->prev;
	}
	while (!(*predicate)(&iterator->data));

	return iterator;
}

Success_T ListIterator_Get(Iterator_T iterator, Object_S* object)
{
	if (!iterator || !object)
	{
		return FAILURE;
	}

	Object_Copy(object, &iterator->data);

	return SUCCESS;
}

Object_S* ListIterator_Access(Iterator_T iterator)
{
	return iterator ? &iterator->data : NULL;
}

Success_T ListIterator_Consume(Iterator_T iterator, Consumer_F consumer)
{
	if (!iterator || !consumer)
	{
		return FAILURE;
	}

	return (*consumer)(&iterator->data);
}

Boolean_T ListIterator_TestIf(Iterator_T iterator, UnaryPredicate_F predicate)
{
	if (!iterator || !predicate)
	{
		return FALSE;
	}

	return (*predicate)(&iterator->data);
}

void List_Init(List_S* list)
{
	if (!list)
	{
		return;
	}

	list->head = list->tail = NULL;
	list->size = 0;

	return;
}

void List_Clear(List_S* list)
{
	if (!list)
	{
		return;
	}

	for (Iterator_T iterator = list->head; list->head; iterator = list->head)
	{
		list->head = list->head->next;
		free(iterator);
	}

	list->tail = NULL;
	list->size = 0;

	return;
}

void List_FreeAndClear(List_S* list, Deleter_F deleter)
{
	if (!list)
	{
		return;
	}

	for (Iterator_T iterator = list->head; list->head; iterator = list->head)
	{
		list->head = list->head->next;

		Object_FreePointer(&iterator->data, deleter);
		free(iterator);
	}

	list->tail = NULL;
	list->size = 0;

	return;
}

size_t List_Size(const List_S* list)
{
	return list ? list->size : 0;
}

Boolean_T List_IsEmpty(const List_S* list)
{
	return list ? list->size == 0 : TRUE;
}

Boolean_T List_Contains(const List_S* list, const Object_S* object)
{
	if (!list || !object)
	{
		return FALSE;
	}

	for (Node_S* node = list->head; node; node = node->next)
	{
		if (Object_Equal(&node->data, object))
		{
			return TRUE;
		}
	}

	return FALSE;
}

size_t List_CountEqual(const List_S* list, const Object_S* object)
{
	if (!list || !object)
	{
		return 0;
	}

	size_t count = 0;
	for (Node_S* node = list->head; node; node = node->next)
	{
		if (Object_Equal(&node->data, object))
		{
			++count;
		}
	}

	return count;
}

size_t List_CountIf(const List_S* list, UnaryPredicate_F predicate)
{
	if (!list || !predicate)
	{
		return 0;
	}

	size_t count = 0;
	for (Node_S* node = list->head; node; node = node->next)
	{
		if ((*predicate)(&node->data))
		{
			++count;
		}
	}
	return count;
}

Boolean_T List_AnyLike(const List_S* list, UnaryPredicate_F predicate)
{
	if (!list || !predicate)
	{
		return FALSE;
	}

	for (Node_S* node = list->head; node; node = node->next)
	{
		if ((*predicate)(&node->data))
		{
			return TRUE;
		}
	}
	return FALSE;
}

Boolean_T List_AllLike(const List_S* list, UnaryPredicate_F predicate)
{
	if (!list || !predicate)
	{
		return FALSE;
	}

	for (Node_S* node = list->head; node; node = node->next)
	{
		if (!(*predicate)(&node->data))
		{
			return FALSE;
		}
	}
	return TRUE;
}

Success_T List_PushFront(List_S* list, const Object_S* object)
{
	if (!list || !object)
	{
		return FAILURE;
	}

	Node_S* node = malloc(sizeof(Node_S));
	if (node)
	{
		++list->size;

		Object_Copy(&node->data, object);

		node->prev = NULL;
		node->next = list->head;

		if (list->head)
		{
			list->head->prev = node;
		}
		list->head = node;
		
		if (!list->tail)
		{
			list->tail = node;
		}

		return SUCCESS;
	}
	else
	{
		return FAILURE;
	}
}

Success_T List_PushBack(List_S* list, const Object_S* object)
{
	if (!list || !object)
	{
		return FAILURE;
	}

	Node_S* node = malloc(sizeof(Node_S));
	if (node)
	{
		++list->size;

		Object_Copy(&node->data, object);

		node->next = NULL;
		node->prev = list->tail;

		if (list->tail)
		{
			list->tail->next = node;
		}
		list->tail = node;
		
		if (!list->head)
		{
			list->head = node;
		}
		
		return SUCCESS;
	}
	else
	{
		return FAILURE;
	}
}

static Iterator_T EmplaceBefore(List_S* list, Iterator_T iterator, const Object_S* object)
{
	Node_S* node = malloc(sizeof(Node_S));
	if (node)
	{
		++list->size;

		Object_Copy(&node->data, object);

		Iterator_T predecessor = iterator->prev;
		if (predecessor)
		{
			node->prev = predecessor;
			predecessor->next = node;
		}
		else
		{
			list->head = node;
		}
		node->next = iterator;
		iterator->prev = node;
	}
	return node;
}

static Iterator_T EmplaceAfter(List_S* list, Iterator_T iterator, const Object_S* object)
{
	Node_S* node = malloc(sizeof(Node_S));
	if (node)
	{
		++list->size;

		Object_Copy(&node->data, object);

		Iterator_T successor = iterator->next;
		if (successor)
		{
			node->prev = successor;
			successor->prev = node;
		}
		else
		{
			list->tail = node;
		}
		node->prev = iterator;
		iterator->next = node;
	}
	return node;
}

Iterator_T List_InsertAt(List_S* list, const Object_S* object, pos_t position)
{
	if (!list || !object)
	{
		return NULL;
	}

	if (position >= 0 && position < list->size)
	{
		Iterator_T iterator = ListIterator_At(list, position);
		return iterator ? EmplaceBefore(list, iterator, object) : NULL;
	}
	else if (position <= -1 && position >= -list->size)
	{
		Iterator_T iterator = ListIterator_At(list, position);
		return iterator ? EmplaceAfter(list, iterator, object) : NULL;
	}
	else if (position == list->size)
	{
		return List_PushBack(list, object) == SUCCESS ? list->tail : NULL;
	}
	else if (position == -list->size - 1)
	{
		return List_PushFront(list, object) == SUCCESS ? list->head : NULL;
	}
	else
	{
		return NULL;
	}
}

Iterator_T List_InsertBefore(List_S* list, Iterator_T iterator, const Object_S* object)
{
	if (!list || !iterator || !object)
	{
		return NULL;
	}

	return EmplaceBefore(list, iterator, object);
}

Iterator_T List_InsertAfter(List_S* list, Iterator_T iterator, const Object_S* object)
{
	if (!list || !iterator || !object)
	{
		return NULL;
	}

	return EmplaceAfter(list, iterator, object);
}

Success_T List_GetFront(List_S* list, Object_S* object)
{
	if (!list || !object)
	{
		return FAILURE;
	}

	if (list->head)
	{
		Object_Copy(object, &list->head->data);

		return SUCCESS;
	}

	return FAILURE;
}

Success_T List_GetBack(List_S* list, Object_S* object)
{
	if (!list || !object)
	{
		return FAILURE;
	}

	if (list->tail)
	{
		Object_Copy(object, &list->tail->data);

		return SUCCESS;
	}

	return FAILURE;
}

Success_T List_GetAt(List_S* list, Object_S* object, pos_t position)
{
	if (!list || !object)
	{
		return FAILURE;
	}

	Iterator_T iterator = ListIterator_At(list, position);
	if (iterator)
	{
		Object_Copy(object, &iterator->data);

		return SUCCESS;
	}

	return FAILURE;
}

Success_T List_GetFirstIf(List_S* list, Object_S* object, UnaryPredicate_F predicate)
{
	if (!list || !object || !predicate)
	{
		return FAILURE;
	}

	Iterator_T iterator = ListIterator_FirstIf(list, predicate);
	if (iterator)
	{
		Object_Copy(object, &iterator->data);

		return SUCCESS;
	}

	return FAILURE;
}

Success_T List_GetLastIf(List_S* list, Object_S* object, UnaryPredicate_F predicate)
{
	if (!list || !object || !predicate)
	{
		return FAILURE;
	}

	Iterator_T iterator = ListIterator_LastIf(list, predicate);
	if (iterator)
	{
		Object_Copy(object, &iterator->data);

		return SUCCESS;
	}

	return FAILURE;
}

Object_S* List_AccessFront(List_S* list)
{
	return list && list->head ? &list->head->data : NULL;
}

Object_S* List_AccessBack(List_S* list)
{
	return list && list->tail ? &list->tail->data : NULL;
}

Object_S* List_AccessAt(List_S* list, pos_t position)
{
	if (!list)
	{
		return NULL;
	}

	Iterator_T iterator = ListIterator_At(list, position);
	
	return iterator ? &iterator->data : NULL;
}

Object_S* List_AccessFirstEqual(List_S* list, const Object_S* object)
{
	if (!list || !object)
	{
		return NULL;
	}

	Iterator_T iterator = ListIterator_FirstEqual(list, object);

	return iterator ? &iterator->data : NULL;
}

Object_S* List_AccessLastEqual(List_S* list, const Object_S* object)
{
	if (!list || !object)
	{
		return NULL;
	}

	Iterator_T iterator = ListIterator_LastEqual(list, object);

	return iterator ? &iterator->data : NULL;
}

Object_S* List_AccessFirstIf(List_S* list, UnaryPredicate_F predicate)
{
	if (!list || !predicate)
	{
		return NULL;
	}

	Iterator_T iterator = ListIterator_FirstIf(list, predicate);
	return iterator ? &iterator->data : NULL;
}

Object_S* List_AccessLastIf(List_S* list, UnaryPredicate_F predicate)
{
	if (!list || !predicate)
	{
		return NULL;
	}

	Iterator_T iterator = ListIterator_LastIf(list, predicate);
	return iterator ? &iterator->data : NULL;
}

Success_T List_PopFront(List_S* list, Object_S* object)
{
	if (!list)
	{
		return FAILURE;
	}

	Node_S* node = list->head;
	if (node)
	{
		--list->size;

		list->head = list->head->next;
		if (list->head)
		{
			list->head->prev = NULL;
		}
		else
		{
			list->tail = NULL;
		}

		if (object)
		{
			Object_Copy(object, &node->data);
		}
		
		free(node);

		return SUCCESS;
	}

	return FAILURE;
}

Success_T List_PopBack(List_S* list, Object_S* object)
{
	if (!list)
	{
		return FAILURE;
	}

	Node_S* node = list->tail;
	if (node)
	{
		--list->size;

		list->tail = list->tail->prev;
		if (list->tail)
		{
			list->tail->next = NULL;
		}
		else
		{
			list->head = NULL;
		}

		if (object)
		{
			Object_Copy(object, &node->data);
		}

		free(node);

		return SUCCESS;
	}

	return FAILURE;
}

static void Unpin(List_S* list, Iterator_T iterator)
{
	if (iterator->prev)
	{
		iterator->prev->next = iterator->next;
	}
	else
	{
		list->head = iterator->next;
	}

	if (iterator->next)
	{
		iterator->next->prev = iterator->prev;
	}
	else
	{
		list->tail = iterator->prev;
	}
}

static Iterator_T DeleteForwards(List_S* list, Iterator_T iterator)
{
	Unpin(list, iterator);

	Iterator_T next = iterator->next;
	free(iterator);

	return next;
}

static Iterator_T DeleteBackwards(List_S* list, Iterator_T iterator)
{
	Unpin(list, iterator);

	Iterator_T prev = iterator->prev;
	free(iterator);

	return prev;
}

Iterator_T List_EraseAt(List_S* list, pos_t position)
{
	if (!list)
	{
		return NULL;
	}

	Iterator_T iterator = ListIterator_At(list, position);
	if (iterator)
	{
		if (position >= 0)
		{
			return DeleteForwards(list, iterator);
		}
		else
		{
			return DeleteBackwards(list, iterator);
		}
	}

	return NULL;
}

Iterator_T List_RemoveFirstEqual(List_S* list, const Object_S* object)
{
	if (!list || !object)
	{
		return NULL;
	}

	Iterator_T iterator = ListIterator_FirstEqual(list, object);
	return iterator ? DeleteForwards(list, iterator) : NULL;
}

Iterator_T List_RemoveLastEqual(List_S* list, const Object_S* object)
{
	if (!list || !object)
	{
		return NULL;
	}

	Iterator_T iterator = ListIterator_LastEqual(list, object);
	return iterator ? DeleteBackwards(list, iterator) : NULL;
}

Iterator_T List_RemoveFirstIf(List_S* list, UnaryPredicate_F predicate)
{
	if (!list || !predicate)
	{
		return NULL;
	}

	Iterator_T iterator = ListIterator_FirstIf(list, predicate);
	return iterator ? DeleteForwards(list, iterator) : NULL;
}

Iterator_T List_RemoveLastIf(List_S* list, UnaryPredicate_F predicate)
{
	if (!list || !predicate)
	{
		return NULL;
	}

	Iterator_T iterator = ListIterator_LastIf(list, predicate);
	return iterator ? DeleteBackwards(list, iterator) : NULL;
}

Iterator_T List_DeleteAt(List_S* list, Iterator_T iterator)
{
	if (!list || !iterator)
	{
		return NULL;
	}

	return DeleteForwards(list, iterator);
}

size_t List_EraseAllBefore(List_S* list, pos_t position)
{
	if (!list || position < -list->size || position >= list->size)
	{
		return 0;
	}

	if (position < 0)
	{
		position += list->size;
	}

	size_t counter;
	for (counter = 0; list->head && counter < position; ++counter)
	{
		List_PopFront(list, NULL);
	}

	return counter;
}

size_t List_EraseAllAfter(List_S* list, pos_t position)
{
	
}

