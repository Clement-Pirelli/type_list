#ifndef TYPE_LIST_FOLDR_H_DEFINED_14641442
#define TYPE_LIST_FOLDR_H_DEFINED_14641442

#include "core.h"
#include "delayed_error.h"

template<
	template<typename, typename> typename,
	typename,
	typename>
	struct foldr
{
	DELAYED_ERROR("foldr<BinaryOp_t, Default_t, T> expects a type_list as its T");
};


template<
	template<typename, typename> typename BinaryOp_t,
	typename Default_t>
	struct foldr<BinaryOp_t, Default_t, type_list<>>
{
	using type = Default_t;
};


template<
	template<typename, typename> typename BinaryOp_t,
	typename Default_t,
	typename T,
	typename... Ts>
	struct foldr<BinaryOp_t, Default_t, type_list<T, Ts...>>
{
private:
	using applied_tail = typename foldr<BinaryOp_t, Default_t, type_list<Ts...>>::type;
public:
	using type = typename BinaryOp_t<T, applied_tail>::type;
};

template<
	template<typename, typename> typename BinaryOp_t,
	typename Default_t,
	typename T>
using foldr_t = typename foldr<BinaryOp_t, Default_t, T>::type;

#endif