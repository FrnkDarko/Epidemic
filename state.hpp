#ifndef STATE_HPP
#define STATE_HPP

struct State
{
	double S;
	double I;
	double R;
	double R_0;
};

bool operator==(State const& l, State const& r);

#endif
