# Day 1: Sonar Sweep

Link to Day 1: https://adventofcode.com/2021/day/1

## Contents
* [Part 1](#part-1)
  * [Problem](#problem-1)
  * [Solution](#solution-1)
* [Part 2](#part-2)
  * [Problem](#problem-2)
  * [Solution](#solution-2)
    * [Sliding Window Approach](#sliding-window-approach)
    * [Mathematical Approach](#mathematical-approach)
* [References](#references)

## Part 1

### Problem 1:

Figure out how quickly the depth increases. To do this, count the **number of times a depth measurement increases** from the previous measurement (there is no measurement before the first measurement).

**Given this [input](input.txt), how many measurements are larger than the previous measurement?**

### Solution 1:

A working solution to the problem expressed in Part 1 is uninteresting compared to the generalized solution discussed in Part 2 so it has been omitted. See the [solution to Part 2](#solution-2).

## Part 2

### Problem 2:

Instead of looking at each measurement individually, consider sums of a **three-measurement sliding window**. The goal now is to count **the number of times the sum of measurements in this sliding window increases** from the previous sum.

Using the same [input](input.txt) from Part 1, consider sums of a three-measurement sliding window. **How many sums are larger than the previous sum?**

### Solution 2:

In general, the solution to this problem can involve either grouping the measurements into three-measurement sliding windows and comparing the sums or taking advantage of the fact that you can instead compare the first value of the first window and the last value of the second window due to a mathematical property (I will explain this later). There may be other approaches to this problem but these are the ones I implemented. I will dub the first approach the "Sliding Window" method and the second approach the "Mathematical" approach.

#### Sliding Window Approach

Located in [Day1.h  at line 83](Day1.h#L83).

For this implementation, I was inspired to use C++20's Ranges by a [blog post by Šimon Tóth](https://itnext.io/modern-c-in-advent-of-code-day1-18f7697d4f6b) where he described how he used Modern C++, i.e., Ranges, to solve Day 1's problem. Šimon relied only on what the STL offered as of C++20 for his implementation but I decided to use a feature not yet in the STL, `std::ranges::views::slide`. I found a standard proposal paper by Tim Song, [P2442R1: Windowing range adaptors: `views::chunk` and `views::slide`](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2021/p2442r1.html), which discusses the implementation of this feature and, at the time, it was very likely for the paper to make it into the C++23 standard according to [P2214R1: A Plan for C++23 Ranges](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2021/p2214r1.html#plan-summary). I made an attempt at implementing `std::ranges::views::slide` myself (you can find that implementation [here](https://github.com/alexriegler/slide)) but it ended up being more difficult than I expected. You can learn more about that attempt in its Github repository. So instead of using the library I implemented, I ended up using the reference implementation of `std::ranges::views::slide` found in the [range-v3 library](https://ericniebler.github.io/range-v3/), which is named [`ranges::views::sliding`](https://ericniebler.github.io/range-v3/#autotoc_md8).

With `ranges::views::sliding` in my toolbelt, the problem because a three-step process. First, create the sliding view. Second, reduce each sliding window to the sum of its elements. Finally, count the number of increases.

Step 1 & 2:
```cpp
auto sliding_sums = std::forward<R>(r)
  | ranges::views::sliding(window_size)
  | ranges::views::transform([](auto item) { return ranges::accumulate(item, 0); });
```

Step 3:
```cpp
auto has_increased = [prev = std::numeric_limits<std::ranges::range_value_t<R>>::max()](std::ranges::range_value_t<R> curr) mutable
{
    bool increased = curr > prev;
    prev = curr;
    return increased;
};
return ranges::count_if(ranges::begin(sliding_sums), ranges::end(sliding_sums), has_increased);
```

The resulting function is named `ac21::experimental::count_increases` and you could do something like this to get the solution to Part 2:

```cpp
auto filename = "input.txt";
if (auto input = std::ifstream{ filename })
{
    auto v = std::ranges::istream_view<int>(input) | ac21::experimental::views::irange_to_vector;
    auto increases = ac21::experimental::count_increases(v, 3);
    std::cout << "Part 2: Increases = " << increases << std::endl;
}
```

#### Mathematical Approach

Located in [Day1.h  at line 13](Day1.h#L13).

This solution utilizes `std::transform_reduce`, a powerful algorithm found in the `<numeric>` Standard Library header. The inspiration for this solution came from a couple of Reddit users on the [r/cpp](https://www.reddit.com/r/cpp/) subreddit, [u/paul2718](https://www.reddit.com/r/cpp/comments/rh1g2j/comment/hoo7tx1/?utm_source=share&utm_medium=web2x&context=3) and [u/Ayjayz](https://www.reddit.com/r/cpp/comments/rh1g2j/comment/hopjacd/?utm_source=share&utm_medium=web2x&context=3).

This simple solution is apparent by observing the fact that only the first value in the first window and the last value in the second window need to be compared. Consider the following example:

```
Naive approach:
A: 199 + 200 + 208       = 607
B:       200 + 208 + 210 = 618
Since, A (607) < B (618), the comparison increased.
```
	
```
Simplified approach:
A: 199 + --- + ---       = 199
B:       --- + --- + 210 = 210
Since, A (199) < B (210), the comparison increased and the solution remains the same.
```

This problem naturally lends itself to the C++ Standard Algorithm `std::transform_reduce`, specifically the overload that takes a BinaryTransformOp and a second, first input iterator. The first, first iterator should be the beginning of the range and the corresponding last iterator should be the end iterator - n, where n is the window size. The second, first iterator should be the beginning iterator + n. The initial value should be 0 since the BinaryReductionOp will be std::plus<>(). The transform operation should be std::less<>() since we want to check if the first element is less than the nth element, i.e., the value increased. This will transform the range into a range of boolean values. The reduction operation should be std::plus<>(), which will sum up the boolean values. This works because the bool's get promoted to int's (https://stackoverflow.com/a/17179339) and the C++ Standard states that "If the source type is bool, the value false is converted to zero and the value true is converted to one" (https://stackoverflow.com/a/5369783).

Thus, all of the work is taken care of by the following one-liner:

```cpp
std::transform_reduce(r.begin(),                // InputIt1 first1,
                      r.end() - window_size,    // InputIt1 last1
                      r.begin() + window_size,  // InputIt2 first2
                      0,                        // T init
                      std::plus<>(),            // BinaryReductionOp reduce
                      std::less<>());           // BinaryTransformOp transform
```

There are some edge-cases to consider as well, e.g., empty range, but I will not delve into those here. See the code to see how those cases are handled.

The function using this approach is named `ac21::count_increases` and you could do use it like this to get the solution to Part 2:

```cpp
auto filename = "input.txt";
if (auto input = std::ifstream{ filename })
{
    auto v = std::vector(std::istream_iterator<int>(input), std::istream_iterator<int>());
    auto increases = ac21::count_increases(v, 3);
    std::cout << "Part 2: Increases = " << increases << std::endl;
}
```

## References
* My implementation of `slide`.
  * https://github.com/alexriegler/slide
* [P2214R0] Barry Revzin, Conor Hoekstra, Tim Song. 2020-10-15. A Plan for C++23 Ranges.
  * https://wg21.link/p2214r0
* [P2442R1] Tim Song. 2021-12-05. Windowing range adaptors: `views::chunk` and `views::slide`.
  * https://wg21.link/p2442r1
* range-v3 library
  * https://ericniebler.github.io/range-v3/
* Šimon Tóth. 2021-12-01. Modern C++ in Advent of Code: Day1.
  * https://itnext.io/modern-c-in-advent-of-code-day1-18f7697d4f6b
* Stack Overflow. adding two bool values in c/c++.
  * https://stackoverflow.com/a/17179339
* Stack Overflow. bool to int conversion.
  * https://stackoverflow.com/a/5369783
* u/paul2718 and u/Ayjayz's comments about using `std::transform_reduce`.
  * u/paul2718: https://www.reddit.com/r/cpp/comments/rh1g2j/comment/hoo7tx1/?utm_source=share&utm_medium=web2x&context=3
  * u/Ayjayz: https://www.reddit.com/r/cpp/comments/rh1g2j/comment/hopjacd/?utm_source=share&utm_medium=web2x&context=3