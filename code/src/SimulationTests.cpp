#include "tronWorld/Coordinates.hpp"
#include "tronWorld/Simulation.hpp"
#include "tronWorld/World.hpp"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

using testing::AllOf;
using testing::Field;
using testing::Pair;
using testing::UnorderedElementsAre;

auto matchLocation(const Location& location)
{
  return AllOf(
    Field("translation", &Location::translation, location.translation),
    Field("orientation", &Location::orientation, location.orientation));
}

auto matchWorldPlayer(const Id& id,
                      const Location& location,
                      const Speed& speed)
{
  return Pair(id,
              AllOf(Field("location",
                          &World::PlayerParameters::location,
                          matchLocation(location)),
                    Field("speed", &World::PlayerParameters::speed, speed)));
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
              AllOf(Field("players",
                          &World::players,
                          UnorderedElementsAre(
                            matchWorldPlayer(p1Id, p1Location, p1Speed),
                            matchWorldPlayer(p2Id, p2Location, p2Speed))),
                    Field("walls", &World::walls, testing::IsEmpty())));
}

TEST_F(SimulationBasicMovementTests, playersMoveInSpecifiedDirection)
{
  auto player1Move =
    Simulation::PlayerMove{ p1Id,
                            Simulation::PlayerMove::Turn::KEEP_AHEAD,
                            Simulation::PlayerMove::Acceleration::NONE };
  auto player2Move =
    Simulation::PlayerMove{ p2Id,
                            Simulation::PlayerMove::Turn::KEEP_AHEAD,
                            Simulation::PlayerMove::Acceleration::NONE };

  simulation.advance({ player1Move, player2Move });

  EXPECT_THAT(
    simulation.getCurrentState(),
    Field("players",
          &World::players,
          UnorderedElementsAre(
            matchWorldPlayer(p1Id, { { 4, 2 }, { 0, -1 } }, p1Speed),
            matchWorldPlayer(p2Id, { { 6, 8 }, { 0, 1 } }, p2Speed))));
}

TEST_F(SimulationBasicMovementTests,
       playersMoveInSpecifiedDirectionMultipleTimes)
{
  auto player1Move =
    Simulation::PlayerMove{ p1Id,
                            Simulation::PlayerMove::Turn::KEEP_AHEAD,
                            Simulation::PlayerMove::Acceleration::NONE };
  auto player2Move =
    Simulation::PlayerMove{ p2Id,
                            Simulation::PlayerMove::Turn::KEEP_AHEAD,
                            Simulation::PlayerMove::Acceleration::NONE };

  simulation.advance({ player1Move, player2Move });
  simulation.advance({ player1Move, player2Move });

  EXPECT_THAT(
    simulation.getCurrentState(),
    Field("players",
          &World::players,
          UnorderedElementsAre(
            matchWorldPlayer(p1Id, { { 4, 0 }, { 0, -1 } }, p1Speed),
            matchWorldPlayer(p2Id, { { 6, 10 }, { 0, 1 } }, p2Speed))));
}

TEST_F(SimulationBasicMovementTests, playersTurnLeftAndRight)
{
  auto player1Move =
    Simulation::PlayerMove{ p1Id,
                            Simulation::PlayerMove::Turn::LEFT,
                            Simulation::PlayerMove::Acceleration::NONE };
  auto player2Move =
    Simulation::PlayerMove{ p2Id,
                            Simulation::PlayerMove::Turn::RIGHT,
                            Simulation::PlayerMove::Acceleration::NONE };

  simulation.advance({ player1Move, player2Move });

  EXPECT_THAT(
    simulation.getCurrentState(),
    Field("players",
          &World::players,
          UnorderedElementsAre(
            matchWorldPlayer(p1Id, { { 2, 4 }, { -1, 0 } }, p1Speed),
            matchWorldPlayer(p2Id, { { 4, 6 }, { -1, 0 } }, p2Speed))));
}

TEST_F(SimulationBasicMovementTests, playersAccelerateAndBrake)
{
  auto player1Move =
    Simulation::PlayerMove{ p1Id,
                            Simulation::PlayerMove::Turn::KEEP_AHEAD,
                            Simulation::PlayerMove::Acceleration::POSITIVE };
  auto player2Move =
    Simulation::PlayerMove{ p2Id,
                            Simulation::PlayerMove::Turn::RIGHT,
                            Simulation::PlayerMove::Acceleration::NEGATIVE };

  simulation.advance({ player1Move, player2Move });

  EXPECT_THAT(simulation.getCurrentState(),
              Field("players",
                    &World::players,
                    UnorderedElementsAre(
                      matchWorldPlayer(p1Id, { { 4, 1 }, { 0, -1 } }, 3),
                      matchWorldPlayer(p2Id, { { 5, 6 }, { -1, 0 } }, 1))));
}

TEST_F(SimulationBasicMovementTests, playersLeaveWallsBehind)
{
  auto player1Move =
    Simulation::PlayerMove{ p1Id,
                            Simulation::PlayerMove::Turn::KEEP_AHEAD,
                            Simulation::PlayerMove::Acceleration::NONE };
  auto player2Move =
    Simulation::PlayerMove{ p2Id,
                            Simulation::PlayerMove::Turn::KEEP_AHEAD,
                            Simulation::PlayerMove::Acceleration::NONE };

  simulation.advance({ player1Move, player2Move });

  EXPECT_THAT(simulation.getCurrentState(),
              Field("walls",
                    &World::walls,
                    UnorderedElementsAre(Pair(Coordinates2d{ 4, 4 }, p1Id),
                                         Pair(Coordinates2d{ 4, 3 }, p1Id),
                                         Pair(Coordinates2d{ 6, 6 }, p2Id),
                                         Pair(Coordinates2d{ 6, 7 }, p2Id))));
}