#include "../type_list.h"
#include <type_traits>


//misc utils
template<typename T>
struct ConstBool
{
	using type = bool;
};

template<typename T>
struct UnwrapType
{
	using type = typename T::type;
};

template<typename T>
struct WrapType
{
	using type = T;
};

template<typename T>
struct IsBool
{
	static constexpr bool value = std::is_same_v<T, bool>;
};

template<typename T>
struct AndInt
{
	using type = type_list<T, int>;
};

template<typename T, typename U>
struct PairToTypeList 
{
	using type = type_list<T, U>;
};

//common
using empty = type_list<>;
using int_singleton = type_list<int>;
using varied_list = type_list<int, float, bool>;
using varied_list_interleaved = type_list<int, int, float, int, bool, int>;
using varied_list_interspersed = type_list<int, int, float, int, bool>;
using ten_list = type_list<int, float, struct X, struct Y, struct Z, size_t, char, int*, struct A, struct B>;
using ten_list_reversed = type_list<struct B, struct A, int*, char, size_t, struct Z, struct Y, struct X, float, int>;
using ten_list_first_five = type_list<int, float, struct X, struct Y, struct Z>;
using ten_list_last_five = type_list<size_t, char, int*, struct A, struct B>;

//cons
static_assert(std::is_same_v<cons_t<int, empty>, int_singleton>);

//length
static_assert(int_singleton::length == 1u);
static_assert(empty::length == 0u);

//map
using bool_list = type_list<bool, bool, bool>;
static_assert(std::is_same_v<map_t<ConstBool, varied_list>, bool_list>);

using wrapped_varied_list = type_list<WrapType<int>, WrapType<float>, WrapType<bool>>;
static_assert(std::is_same_v<map_t<UnwrapType, wrapped_varied_list>, varied_list>);

//foldr
static_assert(std::is_same_v<foldr_t<PairToTypeList, int, empty>, int>);
static_assert(std::is_same_v<foldr_t<PairToTypeList, int, int_singleton>, type_list<int, int>>);
static_assert(std::is_same_v<foldr_t<PairToTypeList, type_list<>, varied_list>, type_list<int, type_list<float, type_list<bool, type_list<>>>>>);

//elem
static_assert(elem_v<bool, bool_list>);
static_assert(elem_v<bool, varied_list>);
static_assert(elem_v<bool, int_singleton> == false);
static_assert(elem_v<bool, empty> == false);

//concat
static_assert(std::is_same_v<concat_t<ten_list_first_five, ten_list_last_five>, ten_list>);
static_assert(std::is_same_v<concat_t<empty, empty>, empty>);
static_assert(std::is_same_v<concat_t<int_singleton, empty>, int_singleton>);
static_assert(std::is_same_v<concat_t<empty, int_singleton>, int_singleton>);

//take
static_assert(std::is_same_v<take_t<0u, int_singleton>, empty>);
static_assert(std::is_same_v<take_t<1u, int_singleton>, int_singleton>);
static_assert(take_t<3u, ten_list>::length == 3u);
static_assert(std::is_same_v<take_t<5u, ten_list>, ten_list_first_five>);

//drop
static_assert(std::is_same_v<drop_t<0u, int_singleton>, int_singleton>);
static_assert(std::is_same_v<drop_t<1u, int_singleton>, empty>);
static_assert(drop_t<3u, ten_list>::length == ten_list::length - 3u);
static_assert(std::is_same_v<take_t<5u, ten_list>, ten_list_first_five>);

//takeWhile
using bool_then_others = type_list<bool, int, float>;
static_assert(std::is_same_v<takeWhile_t<IsBool, empty>, empty>);
static_assert(std::is_same_v<takeWhile_t<IsBool, bool_list>, bool_list>);
static_assert(std::is_same_v<takeWhile_t<IsBool, bool_then_others>, type_list<bool>>);

//dropWhile
static_assert(std::is_same_v<dropWhile_t<IsBool, empty>, empty>);
static_assert(std::is_same_v<dropWhile_t<IsBool, bool_list>, empty>);
static_assert(std::is_same_v<dropWhile_t<IsBool, bool_then_others>, type_list<int, float>>);

//any
static_assert(any_v<IsBool, empty> == false);
static_assert(any_v<IsBool, bool_list>);
static_assert(any_v<IsBool, varied_list>);

//all
static_assert(all_v<IsBool, empty>);
static_assert(all_v<IsBool, bool_list>);
static_assert(all_v<IsBool, varied_list> == false);

//none
static_assert(none_v<IsBool, empty>);
static_assert(none_v<IsBool, varied_list> == false);
static_assert(none_v<IsBool, ten_list>);

//filter
static_assert(std::is_same_v<filter_t<IsBool, empty>, empty>);
static_assert(std::is_same_v<filter_t<IsBool, bool_list>, bool_list>);
static_assert(std::is_same_v<filter_t<IsBool, varied_list>, type_list<bool>>);

//concatMap
static_assert(std::is_same_v<concatMap_t<AndInt, empty>, empty>);
static_assert(std::is_same_v<concatMap_t<AndInt, int_singleton>, type_list<int, int>>);
static_assert(std::is_same_v<concatMap_t<AndInt, varied_list>, varied_list_interleaved>);

//reverse
static_assert(std::is_same_v<reverse_t<ten_list>, ten_list_reversed>);
static_assert(std::is_same_v<reverse_t<empty>, empty>);
static_assert(std::is_same_v<reverse_t<reverse_t<ten_list>>, ten_list>);

//intersperse
static_assert(std::is_same_v<intersperse_t<int, empty>, empty>);
static_assert(std::is_same_v<intersperse_t<int, int_singleton>, int_singleton>);
static_assert(std::is_same_v<intersperse_t<int, varied_list>, varied_list_interspersed>);

//replicate
static_assert(std::is_same_v<replicate_t<0, empty>, empty>);
static_assert(std::is_same_v<replicate_t<1, int>, int_singleton>);
static_assert(std::is_same_v<replicate_t<3, bool>, bool_list>);

//init
static_assert(std::is_same_v<init_t<int_singleton>, empty>);
static_assert(std::is_same_v<init_t<varied_list>, type_list<int, float>>);

//last
static_assert(std::is_same_v<last_t<int_singleton>, int>);
static_assert(std::is_same_v<last_t<varied_list>, bool>);

//singleton
static_assert(std::is_same_v<singleton_t<int>, int_singleton>);

//null
static_assert(null_v<empty>);
static_assert(null_v<int_singleton> == false);
static_assert(null_v<ten_list> == false);