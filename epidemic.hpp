#ifndef EPIDEMIC_HPP
#define EPIDEMIC_HPP

#include <vector>
#include <cassert>
#include <iomanip>
#include <iostream>

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

inline void print(std::vector<State> const& states)
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

#endif
