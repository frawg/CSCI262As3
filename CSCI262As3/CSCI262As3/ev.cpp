/* * * * * * * * * * * * * * * * * * * *
*	Name		: Pang Jin Xiong Joel  *
*	Student ID	: 4643409			   *
*	@author Joel, 4643409			   *
* * * * * * * * * * * * * * * * * * * */
#include "ev.h"

namespace mylib
{
	/**
	Initialize an event with the name and weight

	@param n Name
	@param w Weight
	*/
	ev::ev(std::string n, double w)
	{
		name = n;
		weight = w;
	}

	/**
	Add an Event's measure variable of a day

	@param m Measure variable
	*/
	void ev::addMea(double m)
	{
		measure.push_back(m);
	}

	/**
	Add an Event's test variable of a day

	@param t Test variable
	*/
	void ev::addTest(double t)
	{
		test.push_back(t);
	}

	/**
	Get the average of the measures

	@return Average of all the event's measure data
	*/
	double ev::ave()
	{
		double t = 0.00;
		for (int i = 0; i < measure.size(); i++)
			t += measure.at(i);
		return (t / (double)measure.size());
	}

	/**
	Get sample standard deviation of the measures

	@return Sample standard deviation of all the event's measure data
	*/
	double ev::stdev()
	{
		double t = 0.00;
		double a = ave();
		for (int i = 0; i < measure.size(); i++)
			t += std::pow((measure.at(i) - a), (double)2);
		return std::sqrt((t / (double)(measure.size() - 1)));
	}
}