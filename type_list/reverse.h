#ifndef TYPE_LIST_REVERSE_H_DEFINED_14641442
#define TYPE_LIST_REVERSE_H_DEFINED_14641442

#include "core.h"
#include "delayed_error.h"

namespace details 
{
	template<typename T, typename U>
	struct reverse_impl 
	{
		using type = U;
	};

	template<typename U, typename T, typename...Ts>
	struct reverse_impl<type_list<T, Ts...>, U>
	{
		using type = typename reverse_impl<type_list<Ts...>, cons_t<T, U>>::type;
	};
}

template<typename>
struct reverse
{
	DELAYED_ERROR("reverse<T> expects a type_list as its T");
};

template<typename... Ts>
struct reverse<type_list<Ts...>> : details::reverse_impl<type_list<Ts...>, type_list<>>
{};

template<typename T>
using reverse_t = typename reverse<T>::type;

#endif