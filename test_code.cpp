#include "code.hpp"
#include <type_traits>
#include <string>
#include <cassert>

// this file contains a set of tests that our class template Code<> will need to satisfy

namespace test {

template<typename T, typename U, typename = void>
struct is_equality_comparable
  : std::false_type
  {};

template<typename T, typename U>
struct is_equality_comparable<T, U, typename std::enable_if<true, decltype( std::declval<T const&>() == std::declval<U const&>(), (void)0 )>::type >
  : std::true_type
  {};

}

#define DEFINE_1ARG_EXPRESSION_TRAIT(NAME, ARGNAME, EXPR)  \
namespace test { \
\
template<typename ARGNAME, typename = void> \
struct NAME \
  : std::false_type \
  {}; \
 \
template<typename ARGNAME> \
struct NAME<ARGNAME, typename std::enable_if<true, decltype( EXPR, (void)0 )>::type > \
  : std::true_type \
  {}; \
\
}\


using CurrencyCode = Code<class Currency_tag, 3>;
using AirportCode = Code<class Airport_tag, 3>;

static_assert (!test::is_equality_comparable<CurrencyCode, AirportCode>::value, "unexpectedly comparable");
static_assert (!std::is_convertible<CurrencyCode, AirportCode>::value, "unexpectedly convertible");
static_assert (!std::is_convertible<AirportCode, CurrencyCode>::value, "unexpectedly convertible");
static_assert (sizeof(CurrencyCode) == 3, "excessive sizeof");
static_assert (std::is_trivially_copyable<CurrencyCode>::value, "not trivially copyable");

void test_default_ctor()
{
	CurrencyCode cc;
	CurrencyCode cc2 = uninitialized_code;
	assert (cc == cc2);
	assert (!cc.is_initialized());
}

DEFINE_1ARG_EXPRESSION_TRAIT(is_constructible_from_literal4, T, T{"ABCD"});
DEFINE_1ARG_EXPRESSION_TRAIT(is_constructible_from_literal3, T, T{"ABC"});

void test_literal_ctor()
{
	const CurrencyCode cc1 {"PLN"}, cc2 {"GBP"};
	assert (cc1 == cc1);
	assert (cc1 == CurrencyCode{"PLN"});
	assert (cc1 != cc2);
	assert (cc1.is_initialized());
	assert (cc2.is_initialized());
	
	static_assert ( test::is_constructible_from_literal3<CurrencyCode>::value, "requires construction from ok literal");
	static_assert (!test::is_constructible_from_literal4<CurrencyCode>::value, "unexpected construction from too long literal");
}

void test_string_conv()
{
	CurrencyCode cc = uninitialized_code;
	bool ans = cc.from_string("PLNA");
	assert (!ans);
	ans = cc.from_string("PLN");
	assert (ans);
	assert (cc == CurrencyCode{"PLN"});
	
	assert (cc.to_string() == std::string("PLN"));
	assert (CurrencyCode{}.to_string() == std::string(""));
}

int main ()
{
	test_default_ctor();
	test_literal_ctor();
	test_string_conv();
}
