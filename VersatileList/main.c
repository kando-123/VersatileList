#include "list.h"

#include <stdio.h>

void print_list(List_S* list);

int main(int argc, char* argv[])
{
//	List_S list;
//	List_Init(&list);
//
//#define OBJECTS 5
//	Object_S objects[OBJECTS] =
//	{
//		{.type = Type_Char_e, .value.as_char = 'C'},
//		{.type = Type_Int_e, .value.as_int = 123},
//		{.type = Type_Double_e, .value.as_double = 0.1},
//		{.type = Type_Pointer_e, .value.as_pointer = NULL},
//		{.type = Type_Pointer_e, .value.as_pointer = objects}
//	};
//
//	for (int i = 0; i < OBJECTS; ++i)
//	{
//		if (List_PushBack(&list, &objects[i]) != SUCCESS)
//		{
//			puts("Insertion error!");
//		}
//	}
//
//	print_list(&list);

	return 0;
}

void print_list(List_S* list)
{
	if (!list)
	{
		puts("(null)");
	}
	else
	{
		printf("list (size=%lli)\r\n{\r\n", list->size);
		pos_t i = 0, j = -list->size;
		for (Iterator_T node = list->head; node; node = node->next)
		{
			printf("\t#%lli/%lli ", i++, j++);
			switch (node->data.type)
			{
			case Type_Void_e:
				printf("[ (v) ]\r\n");
				break;
			case Type_Char_e:
				printf("[ (c) %c ]\r\n", node->data.value.as_char);
				break;
			case Type_Short_e:
				printf("[ (s) %hi ]\r\n", node->data.value.as_short);
				break;
			case Type_Int_e:
				printf("[ (i) %i ]\r\n", node->data.value.as_int);
				break;
			case Type_Long_e:
				printf("[ (l) %li ]\r\n", node->data.value.as_long);
				break;
			case Type_LongLong_e:
				printf("[ (L) %lli ]\r\n", node->data.value.as_long_long);
				break;
			case Type_Float_e:
				printf("[ (f) %f ]\r\n", node->data.value.as_float);
				break;
			case Type_Double_e:
				printf("[ (d) %f ]\r\n", node->data.value.as_double);
				break;
			case Type_LongDouble_e:
				printf("[ (D) %Lf ]\r\n", node->data.value.as_long_double);
				break;
			case Type_Pointer_e:
				printf("[ (p) %p ]\r\n", node->data.value.as_pointer);
				break;
			default:
				printf("[ ??? ]\r\n");
			}
		}
		puts("}\r\n");
	}
}

/* -------------------- Collection -------------------- */
#ifdef COLLECTION

enum CollectionType
{
	CollectionType_List_e
	// ...
};
typedef enum CollectionType CollectionType_E;

union CollectionValue
{
	List_S as_list;
	// ...
};
typedef union CollectionValue CollectionValue_U;

struct Collection
{
	CollectionType_E  type;
	CollectionValue_U container;

	void     (*init)    (void* col);
	void     (*clear)   (void* col);
	
	Boolean_T(*is_empty)(void* col);
	size_t   (*size)    (void* col);
	Boolean_T(*contains)(void* col, const Object_S* obj);

	Success_T(*add)     (void* col, const Object_S* obj);
	size_t   (*remove)  (void* col, const Object_S* obj);

	void     (*for_each)(void* col, Consumer_F con);
};
typedef struct Collection Collection_S;

void Collection_InitAsList(Collection_S* collection)
{
	// preclude null...

	collection->type     = CollectionType_List_e;

	collection->init     = List_Init;
	collection->clear    = List_Clear;

	collection->is_empty = List_IsEmpty;
	collection->size     = List_Size;
	collection->contains = List_Contains;

	collection->add      = List_PushBack;
	collection->remove   = List_Remove;

	collection->for_each = List_ForEach;
}

void Collection_Clear(Collection_S* collection)
{
	(*collection->clear)(&collection->container);
}

Boolean_T Collection_IsEmpty(Collection_S* collection)
{
	return (*collection->is_empty)(&collection->container);
}

size_t Collection_Size(Collection_S* collection)
{
	return (*collection->size)(&collection->container);
}

Boolean_T Collection_Contains(Collection_S* collection, const Object_S* object)
{
	return (*collection->contains)(&collection->container, object);
}

Success_T Collection_Add(Collection_S* collection, const Object_S* object)
{
	return (*collection->add)(&collection->container, object);
}

size_t Collection_Remove(Collection_S* collection, const Object_S* object)
{
	return (*collection->remove)(&collection->container, object);
}

void Collection_ForEach(Collelction_S* collection, Consumer_F consumer)
{
	(*collection->for_each)(&collection->container, consumer);
}

Success_T List_Evaluate(List_S* list, Evaluator_F evaluator, Accumulator_F accumulator, Value_U* result)
{
	Value_U* pointers = calloc(list->size, sizeof(void*));
	if (pointers)
	{
		size_t i = 0;
		for (Iterator_T node = list->head; node; node = node->next)
		{
			pointers[i++] = (*evaluator)(&node->data);
		}
		*result = (*accumulator)(pointers, (size_t)list->size);
		free(pointers);

		return SUCCESS;
	}
	else
	{
		return FAILURE;
	}
}
#endif

