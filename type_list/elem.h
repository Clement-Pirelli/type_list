#ifndef TYPE_LIST_ELEM_H_DEFINED_14641442
#define TYPE_LIST_ELEM_H_DEFINED_14641442

#include "core.h"
#include "delayed_error.h"

template<typename, typename>
struct elem
{
	DELAYED_ERROR("elem<Elem_t, T> expects a type_list as its T");
};

template<typename Elem_t>
struct elem<Elem_t, type_list<>> : std::false_type {};

template<typename Elem_t, typename... Tail_ts>
struct elem<Elem_t, type_list<Elem_t, Tail_ts...>> : std::true_type
{};

template<typename Elem_t, typename Head_t, typename... Tail_ts>
struct elem<Elem_t, type_list<Head_t, Tail_ts...>> : elem<Elem_t, type_list<Tail_ts...>>
{};

template<typename Elem_t, typename List_t>
constexpr bool elem_v = elem<Elem_t, List_t>::value;

#endif