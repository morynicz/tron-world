#include "tronWorld/Coordinates.hpp"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

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

class Simulation
{
public:
  Simulation(const std::vector<std::tuple<Id, Location, Speed>>&) {}

  World getCurrentState() const
  {
    return World{ { { 3, Location{ { 4, 4 }, { 0, -1 } }, 2 },
                    { 7, Location{ { 6, 6 }, { 0, 1 } }, 2 } } };
  }
};

auto matchLocation(const Location& location)
{
  return testing::AllOf(
    testing::Field("translation", &Location::translation, location.translation),
    testing::Field(
      "orientation", &Location::orientation, location.orientation));
}

auto matchWorldPlayer(const Id& id,
                      const Location& location,
                      const Speed& speed)
{
  return testing::Pair(
    id,
    testing::AllOf(
      testing::Field("location",
                     &World::PlayerParameters::location,
                     matchLocation(location)),
      testing::Field("speed", &World::PlayerParameters::speed, speed)));
}

TEST(first, first)
{
  Location p1Location{ { 4, 4 }, { 0, -1 } };
  Location p2Location{ { 6, 6 }, { 0, 1 } };
  int p1Id{ 3 };
  int p2Id{ 7 };
  Speed p1Speed{ 2 };
  Speed p2Speed{ 2 };
  Simulation simulation{ { { p1Id, p1Location, p1Speed },
                           { p2Id, p2Location, p2Speed } } };

  EXPECT_THAT(simulation.getCurrentState(),
              testing::Field("players",
                             &World::players,
                             testing::UnorderedElementsAre(
                               matchWorldPlayer(p1Id, p1Location, p1Speed),
                               matchWorldPlayer(p2Id, p2Location, p2Speed))));
}
