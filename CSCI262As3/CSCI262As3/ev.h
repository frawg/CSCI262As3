#include "stdafx.h"

namespace mylib
{
	class ev
	{
	public:
		ev(std::string, double);
		void addMea(double);
		void addTest(double);
		double ave();
		double stdev();
		std::string getName(){ return name; };
		double getWeight(){ return weight; };
		double getTest(int day){ return test.at(day); };
		int getTestSize(){ return test.size(); };
	private:
		std::string name;
		double weight;
		std::vector<double> measure, test;
	};
}