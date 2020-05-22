#include <iostream>
#include <vector>
#include <cassert>

double constexpr beta = 0.1; 
double constexpr gamma = 0.5;

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
  Epidemic(State const& s0, int N) : s0_{s0}, N_{N} {}
  std::vector<State> evolve() const
  {
    std::vector<State> states; 
    states.push_back(s0_);
    auto prev = s0_;
    while (s0_.I != 0) //ho messo gli infetti, perché se sono 0 finisce per forza l'epidemia
    {
      State s;
      double S = prev.S - (beta * prev.I * prev.S) + 0.5;
      if (S < 0){
        S = 0;
      }
      double I = prev.I + (beta * prev.I * prev.S) - (gamma * prev.I) + 0.5;
      if (I > N_){
        I = N_;
      }
      double R = prev.R + (gamma * prev.I);
      if (R > N_){
        R = N_;
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
    std::cout << "Ro = " << state.S * beta / gamma << '\n';
  }
};

int main()
{
  State s0{};
  int N = 100; //popolazione prova
  s0.S = N - 1;
  s0.I = 1;
  Epidemic e{s0, N};
  auto spread = e.evolve();
  print(spread);
}
