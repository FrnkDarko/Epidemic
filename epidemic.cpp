#include <iomanip>

#include "state.hpp"
#include "epidemic.hpp"

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

void print(std::vector<State> const& states)
{
	std::cout << std::setw(10) << "day"
		<< std::setw(10) << "S"
		<< std::setw(10) << "I"
		<< std::setw(10) << "R"
		<< std::setw(10) << "R" << "\u2080" << '\n';
	int day = 1;
	for (auto const& st : states)
	{
		std::cout << std::setw(10) << day
			<< std::setw(10) << static_cast<int>(st.S + 0.5)
			<< std::setw(10) << static_cast<int>(st.I + 0.5)
			<< std::setw(10) << static_cast<int>(st.R + 0.5)
			<< std::setw(10) << st.R_0 << '\n';
		++day;
	}
}