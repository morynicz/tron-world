#include "tronWorld/World.hpp"
#include <ostream>
#include <ranges>

auto makePlayerNodes(
  const std::vector<std::tuple<Id, Location, Speed>>& initialState)
{
  auto players =
    initialState |
    std::views::transform(
      [](const auto& in)
      {
        const auto& [id, location, speed] = in;
        return std::make_pair(id, World::PlayerParameters{ location, speed });
      });
  return decltype(World::players)(players.begin(), players.end());
}

World::World(const std::vector<std::tuple<Id, Location, Speed>>& initialState)
  : players(makePlayerNodes(initialState))
{
}

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