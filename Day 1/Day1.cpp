#include "Day1.h"

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <array>
#include <format>
#include <iostream>
#include <ranges>
#include <vector>

// Example input
namespace
{
	inline constexpr std::array example_input{
		199,
		200,
		208,
		210,
		200,
		207,
		240,
		269,
		260,
		263
	};
}

TEST_CASE("Example")
{
	SECTION("Part 1")
	{
		REQUIRE(AC21::count_increases(example_input) == 7);
	}
	SECTION("Part 2")
	{
		REQUIRE(AC21::count_increases(example_input, 3) == 5);
	}
}

TEST_CASE("Empty vector")
{
	const std::vector<int> input{};
	SECTION("Part 1")
	{
		REQUIRE(AC21::count_increases(input) == 0);
	}
	SECTION("Part 2")
	{
		REQUIRE(AC21::count_increases(input, 3) == 0);
	}
}

TEST_CASE("1 element")
{
	const std::array input{ 1 };
	SECTION("Part 1")
	{
		REQUIRE(AC21::count_increases(input) == 0);
	}
	SECTION("Part 2")
	{
		REQUIRE(AC21::count_increases(input, 3) == 0);
	}
}

TEST_CASE("2 elements, no increases")
{
	const std::array input{ 1, 1 };
	SECTION("Part 1")
	{
		REQUIRE(AC21::count_increases(input) == 0);
	}
	SECTION("Part 2")
	{
		REQUIRE(AC21::count_increases(input, 3) == 0);
	}
}

TEST_CASE("2 elements, 1 increase")
{
	const std::array input{ 1, 2 };
	SECTION("Part 1")
	{
		REQUIRE(AC21::count_increases(input) == 1);
	}
	SECTION("Part 2")
	{
		REQUIRE(AC21::count_increases(input, 3) == 0);
	}
}

TEST_CASE("3 elements, no increases")
{
	const std::array input{ 3, 2, 1 };
	SECTION("Part 1")
	{
		REQUIRE(AC21::count_increases(input) == 0);
	}
	SECTION("Part 2")
	{
		REQUIRE(AC21::count_increases(input, 3) == 0);
	}
}

TEST_CASE("3 elements, 1 increase, last")
{
	const std::array input{ 1, 1, 2 };
	SECTION("Part 1")
	{
		REQUIRE(AC21::count_increases(input) == 1);
	}
	SECTION("Part 2")
	{
		REQUIRE(AC21::count_increases(input, 3) == 0);
	}
}

TEST_CASE("3 elements, 1 increase, second")
{
	const std::array input{ 1, 2, 1 };
	SECTION("Part 1")
	{
		REQUIRE(AC21::count_increases(input) == 1);
	}
	SECTION("Part 2")
	{
		REQUIRE(AC21::count_increases(input, 3) == 0);
	}
}

TEST_CASE("3 elements, 2 increases")
{
	const std::array input{ 1, 2, 3 };
	SECTION("Part 1")
	{
		REQUIRE(AC21::count_increases(input) == 2);
	}
	SECTION("Part 2")
	{
		REQUIRE(AC21::count_increases(input, 3) == 0);
	}
}

TEST_CASE("Solution")
{
	auto filename = std::string{ "input.txt" };
	auto input = std::ifstream{ filename };
	if (!input.is_open())
	{
		throw std::runtime_error{
			std::format("Failed to open \"{}\".\n", filename)
		};
	}
	auto v = std::ranges::istream_view<int>(input) | AC21::views::irange_to_vector;

	SECTION("Part 1")
	{
		auto increases = AC21::count_increases(v);
		std::cout << "1. Increases = " << increases << std::endl;
	}
	SECTION("Part 2")
	{
		auto increases = AC21::count_increases(v, 3);
		std::cout << "2. Increases = " << increases << std::endl;
	}
}
