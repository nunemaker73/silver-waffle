#include <string>
#include "url.hpp"
#include "sec.h"

std::string sec::urlPathQuery(Url u)
{
	std::string s1;
	s1 = u.path();
	Url::Query q;
	q1=u.query();
	if (q.size()<0) {s1+="?";};
	for (const auto& q:q1)
	{
		s1+=q.key();
		s1+="=";
		s1+=q.value();
		s1+="&";
	}
	return s1;
}