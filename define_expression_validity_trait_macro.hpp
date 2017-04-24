// This defines two macros for testing validity of an expression involving 1 or two types.
// E.g., in order to define a a trait for checking equality between two different types,
// you write:
// DEFINE_2ARG_EXPRESSION_TRAIT(is_comparable, T, U, std::declval<const T&>() == std::declval<const U&>())

# define DEFINE_1ARG_EXPRESSION_TRAIT(NAME, ARGNAME, EXPR)    \
  namespace test {                                            \
                                                              \
  template<typename ARGNAME, typename = void>                 \
  struct NAME                                                 \
  : std::false_type                                           \
  {};                                                         \
                                                              \
  template<typename ARGNAME>                                  \
  struct NAME<ARGNAME,                                        \
              typename std::enable_if<true,                   \
                                      decltype(EXPR, (void)0) \
                                     >::type                  \
             >                                                \
  : std::true_type                                            \
  {};                                                         \
                                                              \
  }                                                           \
  
# define DEFINE_2ARG_EXPRESSION_TRAIT(NAME, T, U, EXPR)       \
  namespace test {                                            \
                                                              \
  template<typename T, typename U, typename = void>           \
  struct NAME                                                 \
  : std::false_type                                           \
  {};                                                         \
                                                              \
  template<typename T, typename U>                            \
  struct NAME<T,                                              \
              U,                                              \
              typename std::enable_if<true,                   \
                                      decltype(EXPR, (void)0) \
                                     >::type                  \
             >                                                \
  : std::true_type                                            \
  {};                                                         \
                                                              \
  }                                                           \
  
