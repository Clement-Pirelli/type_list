#ifndef TYPE_LIST_SINGLETON_H_DEFINED_14641442
#define TYPE_LIST_SINGLETON_H_DEFINED_14641442

#include "core.h"

template<typename T>
struct singleton
{
	using type = type_list<T>;
};

template<typename T>
using singleton_t = typename singleton<T>::type;

#endif