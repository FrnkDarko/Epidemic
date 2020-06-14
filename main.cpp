#include <iostream>
#include <vector>
#include <cassert>
#include <iomanip>

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
    //double S;
    //double I;
    //double R; //we can do without these just fine, honestly, i mean, i guess
    while (prev.R != N_)
    {
      State s;
      double S = prev.S - (beta * prev.I * prev.S); //dovrebbe risolvere il problema della riga con S<0 in output
      if (S > 0) //forse un altro nome per questa variabile potrebbe essere utile, si chiama tutto uguale
      {
           s.S = S;
           s.I = prev.I + (beta * prev.I * prev.S) - (gamma * prev.I);
           s.R = prev.R + gamma * prev.I;
      }
      else 
      {
           s.S = 0;
           s.R = prev.R + gamma * prev.I;
           s.I = N_ - s.R;
          
      }
      double sum = s.S + s.I + s.R;
      //assert(sum == N_);
      states.push_back(s);
      prev = s; //prev è definito prima (ln 26), what do we need this for
    }
    return states;
  }
};

void print(std::vector<State> const& states) //really don't know what it's gonna look like
{
    std::cout << std::setw(8) << "S"
        << std::setw(8) << "I"
        << std::setw(8) << "R"
        << std::setw(8) << "R_0" << '\n';
  for (auto const& st : states)
  {
      std::cout << std::setw(8) << static_cast<int>(st.S + 0.5)
          << std::setw(8) << static_cast<int>(st.I + 0.5)
          << std::setw(8) << static_cast<int>(st.R + 0.5)
          << std::setw(8) << st.S * beta / gamma << '\n';
      //do we need an assert here if, like, the sum isn't equal to N_?
      //maybe we can break the loop when R=N_?
      //do we have to redeclare N_ here if we need it?
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
