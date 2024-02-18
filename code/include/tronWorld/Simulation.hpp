#pragma once
#include "tronWorld/World.hpp"

class Simulation
{
public:
  struct PlayerMove
  {
    enum class Turn
    {
      LEFT,
      KEEP_AHEAD,
      RIGHT,
    };

    enum class Acceleration
    {
      CONSTANT
    };

    Id id;
    Turn turn;
    Acceleration acceleration;
  };

  Simulation(const std::vector<std::tuple<Id, Location, Speed>>&);

  World getCurrentState() const;
  void advance(const std::vector<Simulation::PlayerMove>&);

private:
  World state;
};