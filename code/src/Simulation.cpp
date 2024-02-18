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

void Simulation::advance(const std::vector<Simulation::PlayerMove>& moves)
{
  for (const auto& move : moves)
  {
    auto& params = state.players.at(move.id);
    params.location.translation += params.location.orientation * params.speed;
  }
}