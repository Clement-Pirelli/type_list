#ifndef TYPE_LIST_INIT_H_DEFINED_14641442
#define TYPE_LIST_INIT_H_DEFINED_14641442

#include "core.h"
#include "delayed_error.h"

template<typename>
struct init 
{
	DELAYED_ERROR("init<T> expects a non-empty type_list as its T");
};


template<typename T>
struct init<type_list<typename T>> 
{
	using type = type_list<>;
};

template<typename T, typename... Ts>
struct init<type_list<T, Ts...>>
{
	using type = cons_t<T, typename init<type_list<Ts...>>::type>;
};

template<typename T>
using init_t = typename init<T>::type;

#endif