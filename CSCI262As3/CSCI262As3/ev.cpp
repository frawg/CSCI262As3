#include "ev.h"
#include <cmath>

namespace mylib
{
	ev::ev(std::string n, double w)
	{
		name = n;
		weight = w;
	}

	void ev::addMea(double m)
	{
		measure.push_back(m);
	}

	void ev::addTest(double t)
	{
		test.push_back(t);
	}

	double ev::ave()
	{
		double t = 0.00;
		for (int i = 0; i < measure.size(); i++)
			t += measure.at(i);
		return (t / (double)measure.size());
	}

	double ev::stdev()
	{
		double t = 0.00;
		double a = ave();
		for (int i = 0; i < measure.size(); i++)
			t += std::pow((measure.at(i) - a), (double)2);
		return std::sqrt((t / (double)(measure.size() - 1)));
	}
}