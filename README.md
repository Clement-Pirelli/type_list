`type_list` is an MIT-licensed metaprogramming utility for working with lists of types, as described in this [small article](https://clementpirelli.wordpress.com/2022/10/15/lists-of-types-in-c/).

It follows the shape of Haskell's `List`, but for C++ types. 

List operations like folding, mapping, filtering, contatenation and more are available, so you can write code like this:

```cpp
auto my_lambda = [](bool b, SomeType s, int i){ /*stuff here*/ };
using MyLambda_t = decltype(my_lambda);
 
using Params_t = params_of_t<MyLambda_t>;
using FirstTwoArguments_t = take_t<2, Params_t >;
 
static_assert(any_v<IsBool, FirstTwoArguments_t>);
static_assert(filter_t<std::is_integral, Params_t>::length == 2);
```

Beyond its worth as a goof on metaprogramming being essentially a worse version of haskell, it is somewhat useful in writing concise metafunctions and presenting a nice interface to its readers.
