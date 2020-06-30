#include "state.hpp"
#include "epidemic.hpp"

int main()
{	
	int const N = 1000000;	  //trial value
	double const beta = 0.1;  //trial value
	double const gamma = 0.5; //trial value
	State s0{};
	s0.I = 1;
	Epidemic e(s0, N);
	auto spread = e.evolve(beta, gamma);
	std::cout << std::setw(10) << " "
			  << std::setw(10) << "N"
			  << std::setw(10) << "beta"
			  << std::setw(10) << "gamma" << '\n';
	std::cout << std::setw(10) << " "
			  << std::setw(10) << N
			  << std::setw(10) << beta
			  << std::setw(10) << gamma << '\n'
			  << '\n';
	print(spread);
}
