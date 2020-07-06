#include "state.hpp"
#include "epidemic.hpp"
#include "graph.hpp"

std::vector<State> Epidemic::evolve(double const beta, double const gamma) const
{
	assert(beta >= 0. && beta <= 1.);
	if (beta == 0.)
	{
		throw std::runtime_error{ "no epidemic" };
	}
	assert(gamma >= 0. && gamma <= 1.);
	if (gamma == 0.)
	{
		throw std::runtime_error{ "no chance of recovery" };
	}
	std::vector<State> states;
	states.push_back(s0_);
	State prev = states.back();
	while (static_cast<int>(prev.R + 0.5) != N_)
	{
		State s;
		s.R = prev.R + gamma * prev.I;
		double S = prev.S - (beta * prev.I * prev.S);
		if (S > 0.)
		{
			s.S = S;
			s.I = prev.I + (beta * prev.I * prev.S) - (gamma * prev.I);
		}
		else
		{
			s.S = 0.;
			s.I = N_ - s.R;
		}
		s.R_0 = s.S * beta / gamma;
		double sum = s.S + s.I + s.R;
		assert(sum == N_);
		if (prev == s)
		{
			break;
		}
		else
		{
			states.push_back(s);
			prev = s;
		}
	}
	return states;
}

