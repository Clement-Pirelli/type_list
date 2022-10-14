#ifndef TYPE_LIST_INTERSPERSE_H_DEFINED_14641442
#define TYPE_LIST_INTERSPERSE_H_DEFINED_14641442

#include "core.h"
#include "delayed_error.h"

namespace details 
{
	template<typename T, typename U>
	struct intersperse_tail
	{
		using type = type_list<>;
	};

	template<typename T, typename Head_t, typename... Tail_ts>
	struct intersperse_tail<T, type_list<Head_t, Tail_ts...>>
	{
	private:
		using rest = typename intersperse_tail<T, type_list<Tail_ts...>>::type;
		using a = cons_t<Head_t, rest>;
	public:
		using type = cons_t<T, a>;
	};
}

template<typename, typename>
struct intersperse
{
	DELAYED_ERROR("intersperse<T, U> expects a type_list as its U");
};

template<typename T, typename Head_t, typename... Tail_ts>
struct intersperse<T, type_list<Head_t, Tail_ts...>>
{
private:
	using rest = type_list<Tail_ts...>;
	using interspersed_tail = typename details::intersperse_tail<T, rest>::type;
public:
	using type = cons_t<Head_t, interspersed_tail>;
};

template<typename T>
struct intersperse<T, type_list<>>
{
	using type = type_list<>;
};

template<typename T, typename U>
using intersperse_t = typename intersperse<T, U>::type;

#endif