#include "Day1.h"

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <array>
#include <format>
#include <iostream>
#include <ranges>
#include <vector>

TEST_CASE("Solution")
{
    auto filename = "input.txt";
    if (auto input = std::ifstream{ filename })
    {
        SECTION("Standard algorithm")
        {
            auto v = std::vector(std::istream_iterator<int>(input), std::istream_iterator<int>());
            SECTION("Part 1")
            {
                auto increases = ac21::count_increases(v);
                std::cout << "1. Increases = " << increases << std::endl;
            }
            SECTION("Part 2")
            {
                auto increases = ac21::count_increases(v, 3);
                std::cout << "2. Increases = " << increases << std::endl;
            }
        }
        SECTION("Ranges")
        {
            auto v = std::ranges::istream_view<int>(input) | ac21::experimental::views::irange_to_vector;
            SECTION("Part 1")
            {
                auto increases = ac21::experimental::count_increases(v);
                std::cout << "1. Increases = " << increases << std::endl;
            }
            SECTION("Part 2")
            {
                auto increases = ac21::experimental::count_increases(v, 3);
                std::cout << "2. Increases = " << increases << std::endl;
            }
        }
    }
    else
    {
        throw std::runtime_error{
            std::format("Failed to open \"{}\".\n", filename)
        };
    }
}

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
    SECTION("Standard algorithm")
    {
        SECTION("Part 1")
        {
            REQUIRE(ac21::count_increases(example_input) == 7);
        }
        SECTION("Part 2")
        {
            REQUIRE(ac21::count_increases(example_input, 3) == 5);
        }
    }
    SECTION("Ranges")
    {
        SECTION("Part 1")
        {
            REQUIRE(ac21::experimental::count_increases(example_input) == 7);
        }
        SECTION("Part 2")
        {
            REQUIRE(ac21::experimental::count_increases(example_input, 3) == 5);
        }
    }
}

TEST_CASE("Empty vector")
{
    const std::vector<int> input{};
    SECTION("Standard algorithm")
    {
        SECTION("Part 1")
        {
            REQUIRE(ac21::count_increases(input) == 0);
        }
        SECTION("Part 2")
        {
            REQUIRE(ac21::count_increases(input, 3) == 0);
        }
    }
    SECTION("Ranges")
    {
        SECTION("Part 1")
        {
            REQUIRE(ac21::experimental::count_increases(input) == 0);
        }
        SECTION("Part 2")
        {
            REQUIRE(ac21::experimental::count_increases(input, 3) == 0);
        }
    }
}

TEST_CASE("1 element")
{
    const std::array input{ 1 };
    SECTION("Standard algorithm")
    {
        SECTION("Part 1")
        {
            REQUIRE(ac21::count_increases(input) == 0);
        }
        SECTION("Part 2")
        {
            REQUIRE(ac21::count_increases(input, 3) == 0);
        }
    }
    SECTION("Ranges")
    {
        SECTION("Part 1")
        {
            REQUIRE(ac21::experimental::count_increases(input) == 0);
        }
        SECTION("Part 2")
        {
            REQUIRE(ac21::experimental::count_increases(input, 3) == 0);
        }
    }
}

TEST_CASE("2 elements, no increases")
{
    const std::array input{ 1, 1 };
    SECTION("Standard algorithm")
    {
        SECTION("Part 1")
        {
            REQUIRE(ac21::count_increases(input) == 0);
        }
        SECTION("Part 2")
        {
            REQUIRE(ac21::count_increases(input, 3) == 0);
        }
    }
    SECTION("Ranges")
    {
        SECTION("Part 1")
        {
            REQUIRE(ac21::experimental::count_increases(input) == 0);
        }
        SECTION("Part 2")
        {
            REQUIRE(ac21::experimental::count_increases(input, 3) == 0);
        }
    }
}

TEST_CASE("2 elements, 1 increase")
{
    const std::array input{ 1, 2 };
    SECTION("Standard algorithm")
    {
        SECTION("Part 1")
        {
            REQUIRE(ac21::count_increases(input) == 1);
        }
        SECTION("Part 2")
        {
            REQUIRE(ac21::count_increases(input, 3) == 0);
        }
    }
    SECTION("Ranges")
    {
        SECTION("Part 1")
        {
            REQUIRE(ac21::experimental::count_increases(input) == 1);
        }
        SECTION("Part 2")
        {
            REQUIRE(ac21::experimental::count_increases(input, 3) == 0);
        }
    }
}

TEST_CASE("3 elements, no increases")
{
    const std::array input{ 3, 2, 1 };
    SECTION("Standard algorithm")
    {
        SECTION("Part 1")
        {
            REQUIRE(ac21::count_increases(input) == 0);
        }
        SECTION("Part 2")
        {
            REQUIRE(ac21::count_increases(input, 3) == 0);
        }
    }
    SECTION("Ranges")
    {
        SECTION("Part 1")
        {
            REQUIRE(ac21::experimental::count_increases(input) == 0);
        }
        SECTION("Part 2")
        {
            REQUIRE(ac21::experimental::count_increases(input, 3) == 0);
        }
    }
}

TEST_CASE("3 elements, 1 increase, last")
{
    const std::array input{ 1, 1, 2 };
    SECTION("Standard algorithm")
    {
        SECTION("Part 1")
        {
            REQUIRE(ac21::count_increases(input) == 1);
        }
        SECTION("Part 2")
        {
            REQUIRE(ac21::count_increases(input, 3) == 0);
        }
    }
    SECTION("Ranges")
    {
        SECTION("Part 1")
        {
            REQUIRE(ac21::experimental::count_increases(input) == 1);
        }
        SECTION("Part 2")
        {
            REQUIRE(ac21::experimental::count_increases(input, 3) == 0);
        }
    }
}

TEST_CASE("3 elements, 1 increase, second")
{
    const std::array input{ 1, 2, 1 };
    SECTION("Standard algorithm")
    {
        SECTION("Part 1")
        {
            REQUIRE(ac21::count_increases(input) == 1);
        }
        SECTION("Part 2")
        {
            REQUIRE(ac21::count_increases(input, 3) == 0);
        }
    }
    SECTION("Ranges")
    {
        SECTION("Part 1")
        {
            REQUIRE(ac21::experimental::count_increases(input) == 1);
        }
        SECTION("Part 2")
        {
            REQUIRE(ac21::experimental::count_increases(input, 3) == 0);
        }
    }
}

TEST_CASE("3 elements, 2 increases")
{
    const std::array input{ 1, 2, 3 };
    SECTION("Standard algorithm")
    {
        SECTION("Part 1")
        {
            REQUIRE(ac21::count_increases(input) == 2);
        }
        SECTION("Part 2")
        {
            REQUIRE(ac21::count_increases(input, 3) == 0);
        }
    }
    SECTION("Ranges")
    {
        SECTION("Part 1")
        {
            REQUIRE(ac21::experimental::count_increases(input) == 2);
        }
        SECTION("Part 2")
        {
            REQUIRE(ac21::experimental::count_increases(input, 3) == 0);
        }
    }
}

TEST_CASE("5 unsigned elements")
{
    const std::array input{ 1u, 2u, 3u, 4u, 5u };
    SECTION("Standard algorithm")
    {
        SECTION("Part 1")
        {
            REQUIRE(ac21::count_increases(input) == 4);
        }
        SECTION("Part 2")
        {
            REQUIRE(ac21::count_increases(input, 3) == 2);
        }
    }
    SECTION("Ranges")
    {
        SECTION("Part 1")
        {
            REQUIRE(ac21::experimental::count_increases(input) == 4);
        }
        SECTION("Part 2")
        {
            REQUIRE(ac21::experimental::count_increases(input, 3) == 2);
        }
    }
}