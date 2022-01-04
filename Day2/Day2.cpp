#include "Day2.h"

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <sstream>
#include <vector>

using namespace std::literals;

TEST_CASE("Solution")
{
    auto filename = "input.txt";
    if (auto input = std::ifstream{ filename })
    {
        SECTION("Part 1")
        {
            std::cout << "1. Result = " << ac21::calculate_product<ac21::Part::One>(input) << std::endl;
        }
        SECTION("Part 2")
        {
            std::cout << "2. Result = " << ac21::calculate_product<ac21::Part::Two>(input) << std::endl;
        }
    }
    else
    {
        throw std::runtime_error{
            std::format("Failed to open \"{}\".\n", filename)
        };
    }
}

TEST_CASE("Example")
{
    std::stringstream input(
        R"(forward 5
down 5
forward 8
up 3
down 8
forward 2)"
);
    SECTION("Part 1")
    {
        REQUIRE(ac21::calculate_product<ac21::Part::One>(input) == 150);
    }
    SECTION("Part 2")
    {
        REQUIRE(ac21::calculate_product<ac21::Part::Two>(input) == 900);
    }
}