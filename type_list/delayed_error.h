#ifndef TYPE_LIST_DELAYED_ERROR_H_DEFINED_14641442
#define TYPE_LIST_DELAYED_ERROR_H_DEFINED_14641442

#include <type_traits>
#define DELAYED_ERROR(error) \
private: \
template<typename T> \
struct Error \
{ \
static_assert(std::is_same_v<T, T> == false, error); \
using type = T;\
}; \
using error_t = typename Error<void>::type; \
public:

#endif
