#pragma once

#include <gsl/gsl_assert>
#include <range/v3/all.hpp>

#include <algorithm>
#include <concepts>
#include <limits>
#include <numeric>

namespace ac21
{
    /// <summary>
    /// Counts the number of times the sum of values in the sliding window increases from the previous sum.
    /// 
    /// For example, consider sums of a three-measurement sliding window. Consider the following example:
    /// 
    /// 	199  A
    /// 	200  A B
    /// 	208  A B C
    /// 	210    B C D
    /// 	200  E   C D
    /// 	207  E F   D
    /// 	240  E F G
    /// 	269    F G H
    /// 	260      G H
    /// 	263        H
    /// 
    /// Start by comparing the first and second three-measurement windows. The measurements in the first window are marked
    /// A (199, 200, 208); their sum is 199 + 200 + 208 = 607. The second window is marked B (200, 208, 210); its sum is 618.
    /// The sum of measurements in the second window is larger than the sum of the first, so this first comparison increased.
    /// 
    /// A simple solution can be formed by observing the fact that only the first value in the first window and the last value
    /// in the second window need to be compared.
    /// 
    /// 	Naive approach:
    /// 	A: 199 + 200 + 208       = 607
    /// 	B:       200 + 208 + 210 = 618
    /// 	Since, A (607) < B (618), the comparison increased.
    /// 	
    /// 	Simplified approach:
    /// 	A: 199 + --- + ---       = 199
    /// 	B:       --- + --- + 210 = 210
    /// 	Since, A (199) < B (210), the comparison increased and the solution remains the same.
    /// 
    /// This problem naturally lends itself to the C++ standard algorithm std::transform_reduce(), specifically the overload that
    /// takes a BinaryTransformOp and a second, first input iterator. The first, first iterator should be the beginning of the range
    /// and the corresponding last iterator should be the end iterator - n, where n is the window size. The second, first iterator
    /// should be the beginning iterator + n. The initial value should be 0 since the BinaryReductionOp will be std::plus<>(). The
    /// transform operation should be std::less<>() since we want to check if the first element is less than the nth element, i.e.,
    /// the value increased. This will transform the range into a range of boolean values. The reduction operation should be
    /// std::plus<>(), which will sum up the boolean values. This works because the bool's get promoted to int's
    /// (https://stackoverflow.com/a/17179339) and the C++ Standard states that "If the source type is bool, the value false is
    /// converted to zero and the value true is converted to one" (https://stackoverflow.com/a/5369783).
    /// </summary>
    /// <param name="r">The input range of integral values</param>
    /// <param name="window_size">The size of the sliding window</param>
    /// <returns>The number of times the sum of values in the sliding window increased from the previous sum</returns>
    template<std::ranges::input_range R>
        requires std::integral<std::ranges::range_value_t<R>>
    [[nodiscard]] constexpr auto count_increases(R&& r, std::ranges::range_difference_t<R> window_size = 1)
    {
        Expects(window_size > 0);
        if constexpr (std::signed_integral<std::ranges::range_difference_t<R>>)
        {
            if (r.empty() || std::ranges::ssize(r) <= window_size)
            {
                return 0;
            }
        }
        else
        {
            if (r.empty() || std::ranges::size(r) <= window_size)
            {
                return 0;
            }
        }
        return std::transform_reduce(r.begin(), r.end() - window_size, r.begin() + window_size, 0, std::plus<>(), std::less<>());
    }

    namespace experimental
    {
        template<std::ranges::input_range R>
            requires std::integral<std::ranges::range_value_t<R>>
        [[nodiscard]] constexpr auto count_increases(R&& r, std::ranges::range_difference_t<R> window_size = 1)
        {
            Expects(window_size > 0);
            auto has_increased = [prev = std::numeric_limits<std::ranges::range_value_t<R>>::max()](std::ranges::range_value_t<R> curr) mutable
            {
                bool increased = curr > prev;
                prev = curr;
                return increased;
            };
            auto sliding_sums = std::forward<R>(r)
                | ranges::views::sliding(window_size)
                | ranges::views::transform([](auto item)
                    {
                        return ranges::accumulate(item, 0);
                    });
            return ranges::count_if(
                ranges::begin(sliding_sums),
                ranges::end(sliding_sums),
                has_increased);
        }

        namespace views
        {
            namespace detail
            {
                struct irange_to_vector_fn
                {
                    template<std::ranges::input_range R>
                    friend constexpr auto operator|(R&& r, irange_to_vector_fn)
                    {
                        using T = std::ranges::range_value_t<R>;
                        std::vector<T> v{};
                        std::ranges::copy(std::forward<R>(r), std::back_inserter(v));
                        return v;
                    }
                };
            }

            inline constexpr detail::irange_to_vector_fn irange_to_vector;
        }
    }
}