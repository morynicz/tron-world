#pragma once
#include "tronWorld/Coordinates.hpp"
#include <map>
#include <vector>
// #include <format>
#include <ostream>

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
  World(const std::vector<std::tuple<Id, Location, Speed>>& initialState)
  {
    players.emplace(std::get<0>(initialState[0]),
                    PlayerParameters{ std::get<1>(initialState[0]),
                                      std::get<2>(initialState[0]) });
    players.emplace(std::get<0>(initialState[1]),
                    PlayerParameters{ std::get<1>(initialState[1]),
                                      std::get<2>(initialState[1]) });
  }
  std::map<Id, PlayerParameters> players{};
};

// std::ostream& operator<<(std::ostream& os, const Location& input)
// {
//     return os << std::format("{ translation: {}, orientation: {} }",
//     input.translation, input.orientation);
// }

// std::ostream& operator<<(std::ostream& os, const World& world)
// {
//     return os << std::format("{ players: {}}", world.players);
// }

std::ostream& operator<<(std::ostream& os, const Location& input)
{
  return os << "{ translation: " << input.translation
            << ", orientation: " << input.orientation << "}";
}

std::ostream& operator<<(std::ostream& os, const World::PlayerParameters& input)
{
  return os << "{ location: " << input.location << ", speed: " << input.speed
            << "}";
}

std::ostream& operator<<(std::ostream& os, const World& world)
{
  os << "{ players: {";
  for (const auto& playerParameters : world.players)
  {
    os << playerParameters.first << ": " << playerParameters.second << ", ";
  }
  return os << "}}";
}