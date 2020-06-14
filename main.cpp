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
        while (prev.R != N_)
        {
            State s;
            double S = prev.S - (beta * prev.I * prev.S); //forse un altro nome per questa variabile potrebbe essere utile, si chiama tutto uguale
            if (S > 0)
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
            //assert(sum == N_); //honestly this is a bitch
            states.push_back(s);
            prev = s; //prev è definito prima (ln 27), what do we need this for
        }
        return states;
    }
};

void print(std::vector<State> const& states)
{
    std::cout << std::setw(8) << "S"
        << std::setw(8) << "I"
        << std::setw(8) << "R"
        << std::setw(8) << "R_0" << '\n';
    while (s.R != s.S + s.I + s.R) 
    {
        for (auto const& st : states)
        {
            std::cout << std::setw(8) << static_cast<int>(st.S + 0.5)
                << std::setw(8) << static_cast<int>(st.I + 0.5)
                << std::setw(8) << static_cast<int>(st.R + 0.5)
                << std::setw(8) << st.S * beta / gamma << '\n';
        }
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
