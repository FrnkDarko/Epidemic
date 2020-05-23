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
  Epidemic(State const &s0, int N) : s0_{s0}, N_{N} {}
  std::vector<State> evolve()
  {
    std::vector<State> states{s0_};      
    State const &prev = states.back();
    while (prev.R != N_)
    {
      State s{};
      if (prev.S > 0) 
      {
          double S = prev.S - beta * prev.I * prev.S + 0.5;
          double I = prev.I + beta * prev.I * prev.S - gamma * prev.I + 0.5;
          double R = prev.R + gamma * prev.I + 0.5;
      }
      else 
      {
          double S = 0;
          double I = N_ - R;
          double R = prev.R + gamma * prev.I + 0.5;
      }
      s.S = static_cast<int>(S);
      s.I = static_cast<int>(I);
      s.R = static_cast<int>(R);
      assert(N_ == S + I + R);
      states.push_back(s);
    };
    return states;
  };
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
};

int main()
{
  State s0{};
  int N = 100; //trial value
  s0.S = N - 1;
  s0.I = 1;
  Epidemic e{s0, N};
  auto spread = e.evolve();
  print(spread);
}
