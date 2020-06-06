#include <iostream>
#include <vector>
#include <cassert>

double constexpr beta = 0.1; //trial value
double constexpr gamma = 0.5; //trial value

struct State
{
  double S;
  double I;
  double R;
};

class Epidemic
{
  State s0_;
  int const N_;

public:
  Epidemic(State const &s0, int const N) : s0_{s0}, N_{N} {}
  std::vector<State> evolve() const
  {
    std::vector<State> states;  
    states.push_back(s0_);    
    State prev = states.back();
    double S;
    double I;
    double R;
    while (prev.R != N_)
    {
      State s;
      if (prev.S > 0) 
      {
           S = prev.S - (beta * prev.I * prev.S);
           I = prev.I + (beta * prev.I * prev.S) - (gamma * prev.I);
           R = prev.R + gamma * prev.I;
      }
      else 
      {
           S = 0;
           R = prev.R + gamma * prev.I;
           I = N_ - R;
          
      }
      double sum = S + I + R;
      assert(sum == N_);
      s.S = static_cast<int>(S);
      s.I = static_cast<int>(I);
      s.R = static_cast<int>(R) + 0.5;
      states.push_back(s);
      prev = s;
    }
    return states;
  }
};

void print(std::vector<State> const &st)
{
  for (auto const &state : st)
  {
    std::cout << "S = " << state.S << '\n';
    std::cout << "I = " << state.I << '\n';
    std::cout << "R = " << state.R << '\n';
    std::cout << "R_0 = " << state.S * beta / gamma << '\n';
  }
}

int main()
{
  State s0{};
  int const N = 100; //trial value
  s0.S = N - 1;
  s0.I = 1;
  Epidemic e(s0, N);
  auto spread = e.evolve();
  print(spread);
}
