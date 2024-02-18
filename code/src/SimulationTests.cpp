#include "tronWorld/Coordinates.hpp"
#include "tronWorld/Simulation.hpp"
#include "tronWorld/World.hpp"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

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

struct SimulationBasicMovementTests : testing::Test
{
  Location p1Location{ { 4, 4 }, { 0, -1 } };
  Location p2Location{ { 6, 6 }, { 0, 1 } };
  int p1Id{ 3 };
  int p2Id{ 7 };
  Speed p1Speed{ 2 };
  Speed p2Speed{ 2 };
  Simulation simulation{ { { p1Id, p1Location, p1Speed },
                           { p2Id, p2Location, p2Speed } } };
};

TEST_F(SimulationBasicMovementTests, initialStateOfSimulationCanBeRetrieved)
{

  EXPECT_THAT(simulation.getCurrentState(),
              testing::Field("players",
                             &World::players,
                             testing::UnorderedElementsAre(
                               matchWorldPlayer(p1Id, p1Location, p1Speed),
                               matchWorldPlayer(p2Id, p2Location, p2Speed))));
}

TEST_F(SimulationBasicMovementTests, playersMoveInSpecifiedDirection)
{
  auto player1Move =
    Simulation::PlayerMove{ p1Id,
                            Simulation::PlayerMove::Turn::KEEP_AHEAD,
                            Simulation::PlayerMove::Acceleration::CONSTANT };
  auto player2Move =
    Simulation::PlayerMove{ p2Id,
                            Simulation::PlayerMove::Turn::KEEP_AHEAD,
                            Simulation::PlayerMove::Acceleration::CONSTANT };

  simulation.advance({ player1Move, player2Move });

  EXPECT_THAT(
    simulation.getCurrentState(),
    testing::Field("players",
                   &World::players,
                   testing::UnorderedElementsAre(
                     matchWorldPlayer(p1Id, { { 4, 2 }, { 0, -1 } }, p1Speed),
                     matchWorldPlayer(p2Id, { { 6, 8 }, { 0, 1 } }, p2Speed))));
}

TEST_F(SimulationBasicMovementTests,
       playersMoveInSpecifiedDirectionMultipleTimes)
{
  auto player1Move =
    Simulation::PlayerMove{ p1Id,
                            Simulation::PlayerMove::Turn::KEEP_AHEAD,
                            Simulation::PlayerMove::Acceleration::CONSTANT };
  auto player2Move =
    Simulation::PlayerMove{ p2Id,
                            Simulation::PlayerMove::Turn::KEEP_AHEAD,
                            Simulation::PlayerMove::Acceleration::CONSTANT };

  simulation.advance({ player1Move, player2Move });
  simulation.advance({ player1Move, player2Move });

  EXPECT_THAT(simulation.getCurrentState(),
              testing::Field(
                "players",
                &World::players,
                testing::UnorderedElementsAre(
                  matchWorldPlayer(p1Id, { { 4, 0 }, { 0, -1 } }, p1Speed),
                  matchWorldPlayer(p2Id, { { 6, 10 }, { 0, 1 } }, p2Speed))));
}