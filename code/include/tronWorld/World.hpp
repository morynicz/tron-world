#pragma once
#include "tronWorld/Coordinates.hpp"
#include <iosfwd>
#include <map>
#include <vector>

using Speed = int;
using Id = int;

struct Location
{
  const Coordinates2d translation;
  const Coordinates2d orientation;
};

struct World
{
  struct PlayerParameters
  {
    Location location;
    Speed speed;
  };
  World(const std::vector<std::tuple<Id, Location, Speed>>& initialState);
  std::map<Id, PlayerParameters> players{};
};

std::ostream& operator<<(std::ostream& os, const Location& input);
std::ostream& operator<<(std::ostream& os,
                         const World::PlayerParameters& input);
std::ostream& operator<<(std::ostream& os, const World& world);
