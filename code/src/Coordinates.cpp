#include "tronWorld/Coordinates.hpp"
#include <ostream>

Coordinates2d operator+(const Coordinates2d& lhs, Coordinates2d& rhs)
{
  return { lhs.x + rhs.x, lhs.y + rhs.y };
}

Coordinates2d operator*(const Coordinates2d& lhs, int rhs)
{
  return { lhs.x * rhs, lhs.y * rhs };
}

Coordinates2d& Coordinates2d::operator+=(const Coordinates2d& other)
{
  x += other.x;
  y += other.y;
  return *this;
}

bool operator==(const Coordinates2d& lhs, const Coordinates2d& rhs)
{
  return (lhs.x == rhs.x) and (lhs.y == rhs.y);
}

std::ostream& operator<<(std::ostream& os, const Coordinates2d& in)
{
  return os << "{" << in.x << ", " << in.y << "}";
}