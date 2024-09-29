#pragma once
#include <stdlib.h>

enum Type
{
	Type_Void_e,

	Type_Char_e,
	Type_Short_e,
	Type_Int_e,
	Type_Long_e,
	Type_LongLong_e,

	Type_Float_e,
	Type_Double_e,
	Type_LongDouble_e,

	Type_Pointer_e
};
typedef enum Type Type_E;

union Value
{
	char        as_char;
	short       as_short;
	int         as_int;
	long        as_long;
	long long   as_long_long;

	float       as_float;
	double      as_double;
	long double as_long_double;

	void*       as_pointer;
};
typedef union Value Value_U;

struct Object
{
	Type_E  type;
	Value_U value;
};
typedef struct Object Object_S;

typedef Value_U (*Accumulator_F) (Value_U[], size_t);
typedef int     (*Consumer_F)    (Object_S*);
typedef int     (*Comparator_F)  (const Object_S*, const Object_S*);
typedef void    (*Deleter_F)     (void*);
typedef Value_U (*Evaluator_F)   (const Object_S*);

#define TRUE  1
#define FALSE 0
typedef int Boolean_T;

void Object_Init(Object_S* object);
void Object_InitAsChar(Object_S* object, char value);
void Object_InitAsShort(Object_S* object, short value);
void Object_InitAsInt(Object_S* object, int value);
void Object_InitAsLong(Object_S* object, long value);
void Object_InitAsLongLong(Object_S* object, long long value);
void Object_InitAsFloat(Object_S* object, float value);
void Object_InitAsDouble(Object_S* object, double value);
void Object_InitAsLongDouble(Object_S* object, long double value);
void Object_InitAsPointer(Object_S* object, void* value);

void Object_Copy(Object_S* target, const Object_S* origin);
void Object_Swap(Object_S* left, Object_S* right);

void Object_FreePointer(Object_S* object, Deleter_F deleter);

Boolean_T Object_Equal(const Object_S* left, const Object_S* right);
//int Object_Compare(const Object_S* left, const Object_S* right);