#ifndef EPIDEMIC_HPP
#define EPIDEMIC_HPP

#include <vector>
#include <cassert>

class State; //why in the fuck tho

class Epidemic
{
	State s0_;
	int const N_;
public:
	Epidemic(State const& s0, int const N) : s0_{ s0 }, N_{ N }
	{
		assert(N > 1);
	}
	std::vector<State> evolve(double const beta, double const gamma) const;
};

inline void print(std::vector<State> const& states);

#endif
