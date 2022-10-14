#ifndef TYPE_LIST_CONCAT_H_DEFINED_14641442
#define TYPE_LIST_CONCAT_H_DEFINED_14641442

#include "core.h"
#include "delayed_error.h"

template<typename, typename>
struct concat
{
	DELAYED_ERROR("concat<T, U> expects a type_list as its T and U");
};

template<typename Second_t>
struct concat<type_list<>, Second_t>
{
	using type = Second_t;
};

template<>
struct concat<type_list<>, type_list<>> 
{
	using type = type_list<>;
};

template<typename Second_t, typename Head_first_t, typename... Tail_first_ts>
struct concat<type_list<Head_first_t, Tail_first_ts...>, Second_t>
{
private:
	using concat_tail = typename concat<type_list<Tail_first_ts...>, Second_t>::type;
public:
	using type = cons_t<Head_first_t, concat_tail>;
};

template<typename T, typename U>
using concat_t = typename concat<T, U>::type;

#endif