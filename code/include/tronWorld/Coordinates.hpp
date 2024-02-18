#pragma once
#include <iosfwd>

struct Coordinates2d
{
  int x{ 0 };
  int y{ 0 };

  Coordinates2d& operator+=(const Coordinates2d&);
};

Coordinates2d operator+(const Coordinates2d& lhs, const Coordinates2d& rhs);
Coordinates2d operator*(const Coordinates2d&, int);
bool operator==(const Coordinates2d& lhs, const Coordinates2d& rhs);
std::ostream& operator<<(std::ostream& os, const Coordinates2d& in);
