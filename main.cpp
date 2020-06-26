#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <iostream>
#include <vector>
#include <cassert>
#include <iomanip>

struct State
{
	double S;
	double I;
	double R;
	double R_0;
};

bool operator==(State const& l, State const& r)
{
	return l.S == r.S && l.I == r.I && l.R == r.R && l.R_0 == r.R_0;
}

class Epidemic
{
	State s0_;
	int const N_;

public:
	Epidemic(State const& s0, int const N) : s0_{ s0 }, N_{ N } 
	{
		assert(N > 1);
	}
	std::vector<State> evolve(double const beta, double const gamma) const
	{
		assert(beta > 0. && beta <= 1.);
		if (beta == 0.) {
			throw std::runtime_error{ "no epidemic" };
		}
		assert(gamma > 0. && gamma <= 1.);
		if (gamma == 0) {
			throw std::runtime_error{ "no chance of recovery" };
		}
		std::vector <State> states;
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
};

void print(std::vector<State> const& states)
{
	std::cout << std::setw(10) <<"day"
		<< std::setw(10) << "S"
		<< std::setw(10) << "I"
		<< std::setw(10) << "R"
		<< std::setw(10) << "R" <<'\u2080' << '\n'; //should print R with subscript zero, i tried
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

int main()
{
	State s0{};
	int const N = 1000000; //trial value	
	double const beta = 0.1; //trial value
	double const gamma = 0.5; //trial value
	s0.S = N - 1;
	s0.I = 1;
	s0.R_0 = s0.S * beta / gamma;
	Epidemic e(s0, N);
	auto spread = e.evolve(beta, gamma);
	std::cout << std::setw(10) << " "
		<< std::setw(10) << "N"
		<< std::setw(10) << "beta"
		<< std::setw(10) << "gamma" << '\n';
	std::cout << std::setw(10) << " "
		<< std::setw(10) << N
		<< std::setw(10) << beta
		<< std::setw(10) << gamma << '\n' << '\n';
	print(spread);
}

TEST_CASE("Testing Epidemic")
{
	State s0{};
	int const N = 100;
	s0.S = N - 1;
	s0.I = 1; //not defining R_0 bc it doesn't need testing (or does it)
	Epidemic e(s0, N);

	SUBCASE("no epidemic") {
		double const beta = 0.;
		double const gamma = 0.5;
		auto spread = e.evolve(beta, gamma);
	}

	SUBCASE("no chance of recovery") {
		double const beta = 0.5;
		double const gamma = 0.;
		auto spread = e.evolve(beta, gamma);
	}

	SUBCASE("beta=0.1, gamma=0.9") { //test values for beta, gamma
		double const beta = 0.1;
		double const gamma = 0.9;
		auto spread = e.evolve(beta, gamma);
		State const& s1 = spread[1];
		CHECK(s_1.S == doctest::Approx(89.1)); //test 2nd element of spread
		CHECK(s_1.I == doctest::Approx(10));
		CHECK(s_1.R == doctest::Approx(0.9));
		State const& s_last = spread.back();
		CHECK(s_last.S == doctest::Approx(0)); //test last element of spread
		CHECK(s_last.I == doctest::Approx(0));
		CHECK(s_last.R == doctest::Approx(100));
	}

	SUBCASE("beta=0.4, gamma=0.1") { //test values for beta, gamma
		double const beta = 0.4;
		double const gamma = 0.1;
		auto spread = e.evolve(beta, gamma);
		State const& s1 = spread[1];
		CHECK(s_1.S == doctest::Approx(59.4)); //test 2nd element of spread
		CHECK(s_1.I == doctest::Approx(40.5));
		CHECK(s_1.R == doctest::Approx(0.1));
		State const& s_last = spread.back();
		CHECK(s_last.S == doctest::Approx(0)); //test last element of spread
		CHECK(s_last.I == doctest::Approx(0));
		CHECK(s_last.R == doctest::Approx(100));
	}
}
