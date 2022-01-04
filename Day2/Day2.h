#pragma once

#include <iostream>
#include <numeric>
#include <string>

namespace ac21
{
    enum class Part { One, Two };

    template<Part P>
    struct Position
    {
        int horizontal{ 0 };
        int depth{ 0 };
    };

    // Need operator+ for std::accumulate.
    template<Part P>
    Position<P> operator+(Position<P> lhs, const Position<P>& rhs)
    {
        lhs.horizontal += rhs.horizontal;
        lhs.depth += rhs.depth;
        return lhs;
    };

    // Need operator>> for using std::istream_iterator.
    template<Part P>
    std::istream& operator>>(std::istream& is, Position<P>& pos) = delete;

    // This template specialization handles part 1.
    // https://en.cppreference.com/w/cpp/language/template_specialization
    template<>
    std::istream& operator>>(std::istream& is, Position<Part::One>& pos)
    {
        std::string key{};
        int value{};
        is >> key >> value;
        if (key == "forward")
        {
            pos.horizontal = value;
            pos.depth = 0;
        }
        else if (key == "down")
        {
            pos.horizontal = 0;
            pos.depth = value;
        }
        else if (key == "up")
        {
            pos.horizontal = 0;
            pos.depth = -value;
        }
        else
        {
            is.setstate(std::ios::failbit);
        }
        return is;
    }

    // This template specialization is for part 2.
    template<>
    std::istream& operator>>(std::istream& is, Position<Part::Two>& pos)
    {
        static int aim = 0;
        std::string key{};
        int value{};
        is >> key >> value;
        if (key == "forward")
        {
            pos.horizontal = value;
            pos.depth = aim * value;
        }
        else if (key == "down")
        {
            aim += value;
            pos.horizontal = 0;
            pos.depth = 0;
        }
        else if (key == "up")
        {
            aim -= value;
            pos.horizontal = 0;
            pos.depth = 0;
        }
        else
        {
            aim = 0;
            is.setstate(std::ios::failbit);
        }
        return is;
    }

    template<Part P>
    constexpr auto calculate_product(std::istream& is)
    {
        auto p = std::accumulate(
            std::istream_iterator<Position<P>>(is),
            std::istream_iterator<Position<P>>(),
            Position<P>{ 0, 0 }
        );
        return p.horizontal * p.depth;
    }
}