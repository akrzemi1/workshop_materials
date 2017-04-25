#include <array>
#include <string>

constexpr class uninitialized_code_t {} uninitialized_code {};

#if defined __GNUC__
#define LIKELY(X) __builtin_expect(X, 1)
#else
#define LIKELY(X) X
#endif

template <typename /*tag*/, int N>
class Code
{
	std::array<char, N> _data;

public:
    constexpr Code() : _data {} {}
	constexpr Code(uninitialized_code_t) : _data {} {}
	
	explicit Code(const char (&literal)[N + 1]) { std::copy(std::begin(literal), std::end(literal), std::begin(_data));  }
	
	template <int M>
      explicit Code (const char (& literal) [M]) = delete;
	
	constexpr friend bool operator== (Code const& l, Code const& r) { return l._data == r._data; }
	constexpr friend bool operator!= (Code const& l, Code const& r) { return !(l == r); }
	constexpr friend bool operator< (Code const& l, Code const& r) { return l._data < r._data; }
	constexpr friend bool operator> (Code const& l, Code const& r) { return r < l; }
	constexpr friend bool operator<= (Code const& l, Code const& r) { return !(r < l); }
	constexpr friend bool operator>= (Code const& l, Code const& r) { return !(l < r); }
	
	constexpr bool is_initialized() const { return *this != Code{}; }
	
	bool from_string(std::string const& s)
	{
		if (LIKELY(s.length() == N)) {
			std::copy(s.begin(), s.end(), std::begin(_data));
			return true;
		}
		else
			return false;
	}
	
	std::string to_string() const
	{
		if (LIKELY(is_initialized()))
			return std::string(std::begin(_data), std::end(_data));
		else
			return std::string();
	}
};
