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

struct RotationMatrix
{
  const int a1, a2, b1, b2;
};

Coordinates2d operator*(const Coordinates2d& vec, const RotationMatrix& mtx)
{
  return { vec.x * mtx.a1 + vec.y * mtx.a2, vec.x * mtx.b1 + vec.y * mtx.b2 };
}

Coordinates2d& operator*=(Coordinates2d& vec, const RotationMatrix& mtx)
{
  return vec = vec * mtx;
}

const std::map<Simulation::PlayerMove::Turn, RotationMatrix> rotations{
  { Simulation::PlayerMove::Turn::LEFT, { 0, 1, -1, 0 } },
  { Simulation::PlayerMove::Turn::KEEP_AHEAD, { 1, 0, 0, 1 } },
  { Simulation::PlayerMove::Turn::RIGHT, { 0, -1, 1, 0 } }
};

const std::map<Simulation::PlayerMove::Acceleration, int> accelerations{
  { Simulation::PlayerMove::Acceleration::NEGATIVE, -1 },
  { Simulation::PlayerMove::Acceleration::NONE, 0 },
  { Simulation::PlayerMove::Acceleration::POSITIVE, 1 }
};

void Simulation::advance(const std::vector<Simulation::PlayerMove>& moves)
{
  for (const auto& move : moves)
  {
    auto& params = state.players.at(move.id);

    state.walls.insert_or_assign(params.location.translation, move.id);
    auto& orientation = params.location.orientation;
    orientation *= rotations.at(move.turn);
    auto& speed = params.speed;
    speed += accelerations.at(move.acceleration);
    for (Speed s = 0; s < speed; ++s)
    {
      state.walls.insert_or_assign(
        params.location.translation + orientation * s, move.id);
    }

    params.location.translation += orientation * speed;
  }
}
