#pragma once
#include "tronWorld/Coordinates.hpp"
#include <iosfwd>
#include <map>
#include <vector>

using Speed = int;
using Id = int;

struct Location
{
  Coordinates2d translation;
  Coordinates2d orientation;
};

inline auto coordComp = [](const Coordinates2d& lhs, const Coordinates2d& rhs)
{ return std::tie(lhs.x, lhs.y) < std::tie(rhs.x, rhs.y); };

struct World
{
  struct PlayerParameters
  {
    Location location;
    Speed speed;
  };
  World(const std::vector<std::tuple<Id, Location, Speed>>& initialState);
  std::map<Id, PlayerParameters> players{};
  std::map<Coordinates2d, Id, decltype(coordComp)> walls{};
};

std::ostream& operator<<(std::ostream& os, const Location& input);
std::ostream& operator<<(std::ostream& os,
                         const World::PlayerParameters& input);
std::ostream& operator<<(std::ostream& os, const World& world);
