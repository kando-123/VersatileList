#include "object.h"
#include <string.h>

#define PRECLUDE_NULL(arg) if (!(arg)) return

void Object_Init(Object_S* object)
{
	PRECLUDE_NULL(object);

	object->type = Type_Void_e;
	memset(&object->value, 0, sizeof(Value_U));
}

void Object_InitAsChar(Object_S* object, char value)
{
	PRECLUDE_NULL(object);

	object->type = Type_Char_e;
	object->value.as_char = value;
}

void Object_InitAsShort(Object_S* object, short value)
{
	PRECLUDE_NULL(object);

	object->type = Type_Short_e;
	object->value.as_short = value;
}

void Object_InitAsInt(Object_S* object, int value)
{
	PRECLUDE_NULL(object);

	object->type = Type_Int_e;
	object->value.as_int = value;
}

void Object_InitAsLong(Object_S* object, long value)
{
	PRECLUDE_NULL(object);

	object->type = Type_Long_e;
	object->value.as_long = value;
}

void Object_InitAsLongLong(Object_S* object, long long value)
{
	PRECLUDE_NULL(object);

	object->type = Type_LongLong_e;
	object->value.as_long_long = value;
}

void Object_InitAsFloat(Object_S* object, float value)
{
	PRECLUDE_NULL(object);

	object->type = Type_Float_e;
	object->value.as_float = value;
}

void Object_InitAsDouble(Object_S* object, double value)
{
	PRECLUDE_NULL(object);

	object->type = Type_Double_e;
	object->value.as_double = value;
}

void Object_InitAsLongDouble(Object_S* object, long double value)
{
	PRECLUDE_NULL(object);

	object->type = Type_LongDouble_e;
	object->value.as_long_double = value;
}

void Object_InitAsPointer(Object_S* object, void* value)
{
	PRECLUDE_NULL(object);

	object->type = Type_Pointer_e;
	object->value.as_pointer = value;
}

void Object_FreePointer(Object_S* object, Deleter_F deleter)
{
	PRECLUDE_NULL(object);

	if (object->type == Type_Pointer_e && deleter)
	{
		(*deleter)(object->value.as_pointer);
	}
}

void Object_Copy(Object_S* target, const Object_S* origin)
{
	PRECLUDE_NULL(target && origin);

	target->type = origin->type;
	target->value = origin->value;
}

void Object_Swap(Object_S* left, Object_S* right)
{
	if (!left || !right)
	{
		return;
	}

	Type_E type = left->type;
	left->type = right->type;
	right->type = type;

	Value_U value = left->value;
	left->value = right->value;
	right->value = value;
}

Boolean_T Object_Equal(const Object_S* left, const Object_S* right)
{
	if (!left || !right)
	{
		return FALSE;
	}
	else if (left->type != right->type) // Objects of different types are considered different.
	{
		return FALSE;
	}
	else // Objects of the same type are equal if they values are equal.
	{
		switch (left->type)
		{
		case Type_Void_e: // Two Void objects are considered equal indifferently to the value.
			return TRUE;
		case Type_Char_e:
			return left->value.as_char == right->value.as_char;
		case Type_Short_e:
			return left->value.as_short == right->value.as_short;
		case Type_Int_e:
			return left->value.as_int == right->value.as_int;
		case Type_Long_e:
			return left->value.as_long == right->value.as_long;
		case Type_LongLong_e:
			return left->value.as_long_long == right->value.as_long_long;
		case Type_Float_e:
			return left->value.as_float == right->value.as_float;
		case Type_Double_e:
			return left->value.as_double == right->value.as_double;
		case Type_LongDouble_e:
			return left->value.as_long_double == right->value.as_long_double;
		case Type_Pointer_e:
			return left->value.as_pointer == right->value.as_pointer;
		default:
			return FALSE;
		}
	}
}
