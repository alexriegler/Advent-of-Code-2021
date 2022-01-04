# Advent of Code 2021

> My learnings from the Advent of Code 2021.

## Contents
* [About](#about)
* [Days](#days)
* [Tools](#tools)
* [Setup](#setup)

## About
For those who don't know what the Advent of Code (AoC) is, here is a little blurb from the website:

> **Advent of Code** is an Advent calendar of small programming puzzles for a variety of skill sets and skill levels that can be solved in any programming language you like. People use them as a speed contest, interview prep, company training, university coursework, practice problems, or to challenge each other.

For me, I started doing the AoC because I wanted to learn more about the C++ language. I wanted to try to use features that I haven't used before and learn about new ones, such as those coming in C++23. I didn't set out to complete all the days of the AoC. My goal was to emphasize quality over quantity; I wanted to learn as much as I could to improve my skills as a C++ developer.

## Days
Each day has some associated topics and inside its corresponding folder there is a README.md that talks more about what I learned from that day. You can get to the README.md's by following these links:

* [Day 1](./Day1)
  * C++20/C++23 Ranges; `<numeric>` Algorithms.
* [Day 2](./Day2)
  * Operator overloading, template specialization.
* ...


## Tools

* [Microsoft Visual Studio Community 2022 (64-bit) - Preview Version 17.1.0 Preview 1.1](https://visualstudio.microsoft.com/downloads/)
* [vcpkg](https://vcpkg.io/en/getting-started.html)

## Setup
1. Open Visual Studio 2022.
2. From the *Get started* menu, select **Clone a repository**.
3. For *Repository location*, use this repo's git url: https://github.com/alexriegler/Advent-of-Code-2021.git
4. Choose any *Path* you want.
5. Press **Clone**.
6. After the cloning is finished, open the solution file (.sln), if it didn't open automatically.
7. Right-click the project (i.e., the day)  you want to run and select **Set as Startup Project**.
8. Select `Debug -> Start Without Debugging` (Ctrl + F5) or `Debug -> Start Debugging` (F5).

Note: When running a project for the first time, vcpkg may need to install some libraries, which may take a little bit of time.
