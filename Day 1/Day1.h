#pragma once

#include <gsl/gsl_assert>
#include <range/v3/all.hpp>

#include <algorithm>
#include <concepts>
#include <limits>
#include <numeric>

namespace AC21
{
	template<ranges::input_range R>
		requires std::integral<ranges::range_value_t<R>>
	[[nodiscard]] constexpr auto count_increases(R&& r, ranges::range_difference_t<R> window_size = 1)
	{
		Expects(window_size > 0);
		auto has_increased = [prev = std::numeric_limits<std::ranges::range_value_t<R>>::max()](auto curr) mutable
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