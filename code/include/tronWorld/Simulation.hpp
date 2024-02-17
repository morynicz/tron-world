#pragma once
#include "tronWorld/World.hpp"

class Simulation
{
public:
  Simulation(const std::vector<std::tuple<Id, Location, Speed>>&);

  World getCurrentState() const;

private:
  World state;
};