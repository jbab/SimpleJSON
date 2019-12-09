#include "catch.hpp"
#include <optional>
#include <string_view>

template<typename T>
struct parse_result {
    std::optional<T> value;
    char const* next; 
};

constexpr auto match(char c) 
{
    return [c](char const* first, char const* last) -> parse_result<char> {
        if (first == last || *first != c) return { {}, first };
        return { c, first + 1 };
    };
}

TEST_CASE("Match single character", "[parser][match]")
{
    constexpr std::string_view str = "x";
    SECTION("When charater matches, then returns character and advances pointer") {
        auto [value, next] = match('x')(str.begin(), str.end());
        REQUIRE(value == 'x');
        REQUIRE(next == str.end());
    }
    SECTION("When character does not match, then returns nullopt and unmodified pointer") {
        auto [value, next] = match('y')(str.begin(), str.end());
        REQUIRE(value == std::nullopt);
        REQUIRE(next == str.begin());
    }
    SECTION("When string is empty, then returns nullopt and unmodified pointer") {
        auto [value, next] = match('y')(str.end(), str.end());
        REQUIRE(value == std::nullopt);
        REQUIRE(next == str.end());
    }
    SECTION("Can be evaluated in a constexpr context") {
        constexpr parse_result res = match('x')(str.begin(), str.end());
        static_assert(res.value == 'x');
    }
}

