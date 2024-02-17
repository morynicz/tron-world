#pragma once
#include <iosfwd>

struct Coordinates2d
{
  const int x{ 0 };
  const int y{ 0 };
};

Coordinates2d operator+(const Coordinates2d& lhs, Coordinates2d& rhs);
bool operator==(const Coordinates2d& lhs, const Coordinates2d& rhs);
std::ostream& operator<<(std::ostream& os, const Coordinates2d& in);
