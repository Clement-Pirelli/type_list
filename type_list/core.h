
#ifndef TYPE_LIST_CORE_H_DEFINED_14641442
#define TYPE_LIST_CORE_H_DEFINED_14641442

#include "delayed_error.h"

struct Nil;

template<typename...>
struct type_list
{
	static constexpr size_t length = 0u;
	using head = Nil;
};

template<typename Head_t, typename... Tail_ts>
struct type_list<Head_t, Tail_ts...>
{
	static constexpr size_t length = sizeof...(Tail_ts) + 1u;
	using head = Head_t;
	using tail = type_list<Tail_ts...>;
};


template<typename, typename>
struct cons 
{
	DELAYED_ERROR("cons<T, U> expects a type_list as its U");
};

template<typename T, typename... Ts>
struct cons<T, type_list<Ts...>>
{
	using type = type_list<T, Ts...>;
};

template<typename T, typename... Ts>
using cons_t = typename cons<T, Ts...>::type;

template<typename T>
struct head 
{
	using type = typename T::head;
};

template<typename T>
using head_t = typename head<T>::type;

template<typename T>
struct tail 
{
	using type = typename T::tail;
};

template<typename T>
using tail_t = typename tail<T>::type;

template<typename T>
struct length 
{
	static constexpr size_t value = T::length;
};

template<typename T>
constexpr size_t length_v = length<T>::value;


#endif