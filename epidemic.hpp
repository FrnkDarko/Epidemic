#ifndef EPIDEMIC_HPP
#define EPIDEMIC_HPP

#include <vector>
#include <cassert>
#include <iomanip>
#include <iostream>

class State; 

class Epidemic
{
	State s0_;
	int const N_;
public:
	Epidemic(State const& s0, int const N) : s0_{ s0 }, N_{ N }
	{
		assert(N > 0);
		assert(s0.I >= 0.);
		if (s0.I == 0.)
		{
			throw std::runtime_error{ "no infected subjects" };
		}
		if (N < s0.I)
		{
			throw std::runtime_error{ "population must be at least equal to the number of infected subjects" };
		}
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
	std::cout << '\n';
}

inline void drawS(std::vector<State> const& states, int scale)
{
	int dayS = 1;
	std::cout << std::setw(10) << " "
		<< "Susceptible (scale: " << std::scientific << scale << ")" << '\n'; 
	for (auto const& st : states)
	{
		std::cout << std::setw(10) << dayS << " ";
		for (int i = 0; i < st.S / scale; ++i)
		{
			std::cout << "*";
		}
		std::cout << '\n';
		++dayS;
	}
	std::cout << '\n';
}

inline void drawI(std::vector<State> const& states, int scale) 
{
	int dayI = 1;
	std::cout << std::setw(10) << " "
		<< "Infected (scale: " << std::scientific << scale << ")" << '\n';
	for (auto const& st : states)
	{
		std::cout << std::setw(10) << dayI << " ";
		for (int i = 0; i < st.I / scale; ++i)
		{
			std::cout << "*";
		}
		std::cout << '\n';
		++dayI;
	}
	std::cout << '\n';
}

inline void drawR(std::vector<State> const& states, int scale) 
{
	int dayR = 1;
	std::cout << std::setw(10) << " "
		<< "Recovered (scale: " << std::scientific << scale << ")" << '\n';
	for (auto const& st : states)
	{
		std::cout << std::setw(10) << dayR << " ";
		for (int i = 0; i < st.R / scale; ++i)
		{
			std::cout << "*";
		}
		std::cout << '\n';
		++dayR;
	}
}

enum class Graph { S, I, R, all };

inline void draw(std::vector<State> const& states, int scale, Graph graph)
{
	switch (graph)
	{
	case Graph::S:
		drawS(states, scale);
		break;
	case Graph::I:
		drawI(states, scale);
		break;
	case Graph::R:
		drawR(states, scale);
		break;
	case Graph::all:
		drawS(states, scale);
		drawI(states, scale);
		drawR(states, scale);
		break;
	default:
		break;
	}
}

#endif
