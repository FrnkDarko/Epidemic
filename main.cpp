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
		assert(beta >= 0 && beta <= 1); //two separate asserts?
		assert(gamma >= 0 && gamma <= 1); //two separate asserts?
		//maybe runtime errors for beta, gamma = 0 / = 1? we should discuss this
		std::vector <State> states;
		states.push_back(s0_);
		State prev = states.back();
		while (static_cast<int>(prev.R + 0.5) != N_)
		{
			State s;
			s.R = prev.R + gamma * prev.I;
			double S = prev.S - (beta * prev.I * prev.S);
			if (S > 0)
			{
				s.S = S;
				s.I = prev.I + (beta * prev.I * prev.S) - (gamma * prev.I);
			}
			else
			{
				s.S = 0;
				s.I = N_ - s.R;
			}
			s.R_0 = s.S * beta / gamma;
			double sum = s.S + s.I + s.R;
			assert(sum == N_);
			states.push_back(s);
			prev = s;
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
		<< std::setw(10) << "R_0" << '\n';
	int i = 0;
	for (auto const& st : states)
	{
		std::cout << std::setw(10) << i
			<< std::setw(10) << static_cast<int>(st.S + 0.5)
			<< std::setw(10) << static_cast<int>(st.I + 0.5)
			<< std::setw(10) << static_cast<int>(st.R + 0.5)
			<< std::setw(10) << st.R_0 << '\n';
		++i;
	}
}

int main()
{
	State s0{};
	int const N = 1000000; //trial value
	s0.S = N - 1;
	s0.I = 1;
	Epidemic e(s0, N);
	double const beta = 0.03; //trial value
	double const gamma = 0.5;; //trial value
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
