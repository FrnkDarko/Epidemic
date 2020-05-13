# Pandemic
Progetto per esame di programmazione per la fisica

#include <iostream>
#include <vector>

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
    /* loop for con equazioni
    double S=S_prev-B*I_prev*S_prev
    double I=I_prev+B*I_prev*S_prev-G*I_prev
    double R=R_prev+G*I_prev
    aggiungere 0.5 a S, I, R e fare cast a int
    assert(N=S+I+R)
    */
    return states;
  };
};

void print(){};

int main() {
  State s0{};
  int N;
  s0.S = n - 1;
  s0.I = 1;
  Epidemic e{s0, N};
  print();
}
