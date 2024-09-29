#pragma once
#include "object.h"
#include <stdlib.h>

/* ----- Structure of the List ----- */

struct Node
{
	Object_S     data;

	struct Node* prev;
	struct Node* next;
};
typedef struct Node Node_S;

typedef signed long long int pos_t;

struct List
{
	pos_t   size;
	Node_S* head;
	Node_S* tail;
};
typedef struct List List_S;

/* ----- Function Types ----- */

typedef Boolean_T(*UnaryPredicate_F) (const Object_S*);
typedef Boolean_T(*BinaryPredicate_F)(const Object_S*, const Object_S*);

/* ----- Code Error Type ----- */

typedef int Success_T;
#define SUCCESS 0

/* ----- Iterator Type ----- */

typedef Node_S* Iterator_T;

/* ----- Iterator Creation ----- */

Iterator_T ListIterator_Front     (List_S* list);
Iterator_T ListIterator_Back      (List_S* list);

Iterator_T ListIterator_At        (List_S* list, pos_t position);

Iterator_T ListIterator_FirstEqual(List_S* list, const Object_S* object);
Iterator_T ListIterator_LastEqual (List_S* list, const Object_S* object);

Iterator_T ListIterator_FirstIf   (List_S* list, UnaryPredicate_F predicate);
Iterator_T ListIterator_LastIf    (List_S* list, UnaryPredicate_F predicate);

/* ----- Iterator Shifting ----- */

Iterator_T ListIterator_Next         (Iterator_T iterator);
Iterator_T ListIterator_Previous     (Iterator_T iterator);

Iterator_T ListIterator_Advance      (Iterator_T iterator, pos_t offset);

Iterator_T ListIterator_NextEqual    (Iterator_T iterator, const Object_S* object);
Iterator_T ListIterator_PreviousEqual(Iterator_T iterator, const Object_S* object);

Iterator_T ListIterator_NextSame     (Iterator_T iterator);
Iterator_T ListIterator_PreviousSame (Iterator_T iterator);

Iterator_T ListIterator_NextIf       (Iterator_T iterator, UnaryPredicate_F predicate);
Iterator_T ListIterator_PreviousIf   (Iterator_T iterator, UnaryPredicate_F predicate);

/* ----- Iterator Data Operations ----- */

Success_T ListIterator_Get    (Iterator_T iterator, Object_S* object);
Object_S* ListIterator_Access (Iterator_T iterator);

Success_T ListIterator_Consume(Iterator_T iterator, Consumer_F consumer);
Boolean_T ListIterator_TestIf (Iterator_T iterator, UnaryPredicate_F predicate);

/* ----- List Creation & Destruction ----- */

void List_Init (List_S* list);
void List_Clear(List_S* list);
void List_FreeAndClear(List_S* list, Deleter_F deleter);

/* ----- List Descriptors ----- */

size_t    List_Size      (const List_S* list);
Boolean_T List_IsEmpty   (const List_S* list);
Boolean_T List_Contains  (const List_S* list, const Object_S* object);

size_t    List_CountEqual(const List_S* list, const Object_S* object);
size_t    List_CountIf   (const List_S* list, UnaryPredicate_F predicate);

Boolean_T List_AnyLike   (const List_S* list, UnaryPredicate_F predicate);
Boolean_T List_AllLike   (const List_S* list, UnaryPredicate_F predicate);

/* ----- Insertion ----- */

Success_T  List_PushFront   (List_S* list, const Object_S* object);
Success_T  List_PushBack    (List_S* list, const Object_S* object);

Iterator_T List_InsertAt    (List_S* list, const Object_S* object, pos_t position);

Iterator_T List_InsertBefore(List_S* list, Iterator_T iterator, const Object_S* object);
Iterator_T List_InsertAfter (List_S* list, Iterator_T iterator, const Object_S* object);

/* ----- Retrieval ----- */

Success_T List_GetFront     (List_S* list, Object_S* object);
Success_T List_GetBack      (List_S* list, Object_S* object);
Success_T List_GetAt        (List_S* list, Object_S* object, pos_t position);
Success_T List_GetFirstIf   (List_S* list, Object_S* object, UnaryPredicate_F predicate);
Success_T List_GetLastIf    (List_S* list, Object_S* object, UnaryPredicate_F predicate);

Object_S* List_AccessFront     (List_S* list);
Object_S* List_AccessBack      (List_S* list);
Object_S* List_AccessAt        (List_S* list, pos_t position);
Object_S* List_AccessFirstEqual(List_S* list, const Object_S* object);
Object_S* List_AccessLastEqual (List_S* list, const Object_S* object);
Object_S* List_AccessFirstIf   (List_S* list, UnaryPredicate_F predicate);
Object_S* List_AccessLastIf    (List_S* list, UnaryPredicate_F predicate);

/* ----- Removal ----- */

Success_T  List_PopFront         (List_S* list, Object_S* object);
Success_T  List_PopBack          (List_S* list, Object_S* object);

Iterator_T List_EraseAt          (List_S* list, pos_t position);

Iterator_T List_RemoveFirstEqual (List_S* list, const Object_S* object);
Iterator_T List_RemoveLastEqual  (List_S* list, const Object_S* object);

Iterator_T List_RemoveFirstIf    (List_S* list, UnaryPredicate_F predicate);
Iterator_T List_RemoveLastIf     (List_S* list, UnaryPredicate_F predicate);

Iterator_T List_DeleteAt         (List_S* list, Iterator_T iterator);

size_t     List_EraseAllBefore   (List_S* list, pos_t position);
size_t     List_EraseAllAfter    (List_S* list, pos_t position);
size_t     List_EraseRange       (List_S* list, pos_t position, size_t length);

size_t     List_RemoveAllEqual   (List_S* list, const Object_S* object);

size_t     List_DeleteAllBefore  (List_S* list, Iterator_T iterator);
size_t     List_DeleteAllAfter   (List_S* list, Iterator_T iterator);
size_t     List_DeleteRangeBefore(List_S* list, Iterator_T iterator, size_t length);
size_t     List_DeleteRangeAfter (List_S* list, Iterator_T iterator, size_t length);
size_t     List_DeleteRange      (List_S* list, Iterator_T begin, Iterator_T end);

Success_T  List_FreeAndPopFront         (List_S* list, Object_S* object, Deleter_F deleter);
Success_T  List_FreeAndPopBack          (List_S* list, Object_S* object, Deleter_F deleter);

Iterator_T List_FreeAndEraseAt          (List_S* list, pos_t position, Deleter_F deleter);

Iterator_T List_FreeAndRemoveFirstEqual (List_S* list, const Object_S* object, Deleter_F deleter);
Iterator_T List_FreeAndRemoveLastEqual  (List_S* list, const Object_S* object, Deleter_F deleter);
Iterator_T List_FreeAndRemoveFirstIf    (List_S* list, const Object_S* object, Deleter_F deleter);
Iterator_T List_FreeAndRemoveLastIf     (List_S* list, const Object_S* object, Deleter_F deleter);

Iterator_T List_FreeAndDeleteAt         (List_S* list, Iterator_T iterator, Deleter_F deleter);

size_t     List_FreeAndEraseAllBefore   (List_S* list, pos_t position, Deleter_F deleter);
size_t     List_FreeAndEraseAllAfter    (List_S* list, pos_t position, Deleter_F deleter);
size_t     List_FreeAndEraseRange       (List_S* list, pos_t position, size_t length, Deleter_F deleter);

size_t     List_FreeAndRemoveAllEqual   (List_S* list, const Object_S* object, Deleter_F deleter);

size_t     List_FreeAndDeleteAllBefore  (List_S* list, Iterator_T iterator, Deleter_F deleter);
size_t     List_FreeAndDeleteAllAfter   (List_S* list, Iterator_T iterator, Deleter_F deleter);
size_t     List_FreeAndDeleteRangeBefore(List_S* list, Iterator_T iterator, size_t length, Deleter_F deleter);
size_t     List_FreeAndDeleteRangeAfter (List_S* list, Iterator_T iterator, size_t length, Deleter_F deleter);
size_t     List_FreeAndDeleteRange      (List_S* list, Iterator_T begin, Iterator_T end, Deleter_F deleter);

/* ----- Other ----- */

size_t    List_Merge   (List_S* list, List_S* other);
void      List_ForEach (List_S* list, Consumer_F consumer);
void      List_Sort    (List_S* list, Comparator_F comparator);
void      List_Rotate  (List_S* list, Boolean_T forward);
void      List_Reverse (List_S* list);

Success_T List_Evaluate(List_S* list, Evaluator_F evaluator, Accumulator_F accumulator, Value_U* result);

/* ----- Aliases ----- */

#define Queue_S    List_S
#define Queue_Push List_PushFront
#define Queue_Pop  List_PopBack

#define Stack_S    List_S
#define Stack_Push List_PushBack
#define Stack_Pop  List_PopBack
