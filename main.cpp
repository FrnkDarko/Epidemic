
#include <iostream>
#include <vector>
#include <cassert>

double constexpr beta = 0; //probably not the best way to do this
double constexpr gamma = 0;

struct State {
  double S;
  double I;
  double R;
};

class Epidemic {
  State s0_;
  int const N_;

 public:
  Epidemic(State const& s0, int N) : s0_{s0}, N_{N} {}
  std::vector<State> evolve() {
    std::vector<State> states{s0_};
    int period; //don't know if it should be here or what
    for (int i = 0; i != period; ++i) {
        State s{};
        State const& prev = states.back();
        double S = prev.S - beta * prev.I * prev.S + 0.5;
        double I = prev.I + beta * prev.I * prev.S - gamma * prev.I + 0.5;
        double R = prev.R + gamma * prev.I + 0.5;
        s.S = static_cast<int>(S);
        s.I = static_cast<int>(I);
        s.R = static_cast<int>(R);
        assert(N_ == S + I + R);
        states.push_back(s);
    };
    return states;
  };
};

void print(){};

int main() {
  State s0{};
  int N;
  s0.S = N - 1;
  s0.I = 1;
  Epidemic e{s0, N};
  e.evolve();
  print();
}
