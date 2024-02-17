#include "tronWorld/Simulation.hpp"

Simulation::Simulation(
  const std::vector<std::tuple<Id, Location, Speed>>& initialState)
  : state(initialState)
{
}

World Simulation::getCurrentState() const
{
  return state;
}