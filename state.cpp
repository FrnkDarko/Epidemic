#include "state.hpp"

bool operator==(State const& l, State const& r)
{
	return l.S == r.S && l.I == r.I && l.R == r.R && l.R_0 == r.R_0;
}