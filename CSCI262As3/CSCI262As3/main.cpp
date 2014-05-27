/* * * * * * * * * * * * * * * * * * * *
*	Name		: Pang Jin Xiong Joel  *
*	Student ID	: 4643409              *
* * * * * * * * * * * * * * * * * * * */
#include "stdafx.h"
#include "ev.h"
#include "mysmalllib.h"
#include <iomanip>

inline void formString(std::vector<std::string> t1, std::vector<std::string> &t2)
{
	for (int i = 0; i < t1.size(); i++)
	{
		mylib::delimString(t1.at(i), ':', t2);
		if (t2.back().empty())
			t2.pop_back();
	}
}

inline double threshold(std::vector<mylib::ev> &evnts)
{
	double a = 0.00;
	for (int i = 0; i < evnts.size(); i++)
		a += evnts.at(i).getWeight();
	return (a * (double)2);
}

double tDistance(std::vector<mylib::ev> &evnts, int n, std::string &formTest, std::string &alarms)
{
	double d = 0.00;
	int hit = 0;
	std::stringstream ss;

	for (int i = 0; i < evnts.size(); i++)
	{
		ss << evnts.at(i).getTest(n);
		ss << ':';
		d += ((std::abs(evnts.at(i).getTest(n) - evnts.at(i).ave()) / evnts.at(i).stdev()) * evnts.at(i).getWeight());
		//std::cout << evnts.at(i).getTest(n) << " | ";
		//d += ((evnts.at(i).getTest(n) - evnts.at(i).ave()) / evnts.at(i).stdev()) * evnts.at(i).getWeight();
		if ((d - (threshold(evnts) * (double)hit)) > threshold(evnts))
		{
			hit += 1;
			alarms.append(" Yes");
		}
		//else
		//	alarms.append(" No");
	}
	if (hit == 0)
		alarms = " No";
	formTest = ss.str();
	//formTest.erase(formTest.end());
	//std::cout << std::endl;
	return d;
}

std::string cLimit(std::string s, int limit)
{
	if (s.length() > limit)
	{
		return s.substr(0, limit) + "...";
	}
	return s;
}

inline std::string setP(double data, int m, bool pre)
{
	std::stringstream ss;
	if (pre)
		ss << std::fixed;
	ss << std::setprecision(m) << data;
	return ss.str();
}

void display(std::vector<mylib::ev> &evnts)
{
	std::cout << std::setw(30) << std::left << "Events" << std::setw(15) << std::right << "Average"
		<< std::setw(15) << std::right << "Stdev" << std::setw(15) << std::right << "Weight" << std::endl;
	std::cout << "-----------------------------------------------------------------------------" << std::endl;
	for (int i = 0; i < evnts.size(); i++)
	{
		std::cout << std::setw(30) << std::left << cLimit(evnts.at(i).getName(), 25);
		std::cout << std::setw(15) << std::right << setP(evnts.at(i).ave(), 2, true);
		std::cout << std::setw(15) << std::right << setP(evnts.at(i).stdev(), 2, true);
		std::cout << std::setw(11) << "" << setP(evnts.at(i).getWeight(), 2, false) << std::endl;
	}
	//std::cout << std::endl;
	std::cout << "-----------------------------------------------------------------------------" << std::endl;
	std::cout << std::setw(20) << std::left << "Threshold:" << threshold(evnts) << '\n' << std::endl;

	for (int i = 0; i < evnts.at(0).getTestSize(); i++)
	{
		std::string alarms, formTest;
		double d = tDistance(evnts, i, formTest, alarms);
		std::cout << "Line " << i + 1 << " -- " << std::setw(20) << std::left << formTest << std::setw(15) << std::right
			<< "Distance: " << std::setw(10) << std::left << setP(d, 2, true)
			<< std::setw(6) << std::right << "Alarms:" << alarms << std::endl;
	}
}

int main(int argc, char* argv[])
{
	std::vector<mylib::ev> evnts;
	std::string evntxt(argv[1], 256), evntbase(argv[2], 256), evntest(argv[3], 256);
	std::vector<std::string> temp1, temp2;
	int evntSize;

	mylib::readFile(evntxt, temp1);
	evntSize = std::atoi(temp1.at(0).c_str());
	temp1.erase(temp1.begin());
	formString(temp1, temp2);
	temp1.clear();

	if ((temp2.size() % 2) != 0 || (temp2.size() / 2) != evntSize)
	{
		std::cout << "Formating in " << evntxt << " error." << std::endl;
		return 0;
	}
	else
	{
		for (int i = 0; i < (temp2.size() / 2); i++)
		{
			evnts.push_back(mylib::ev(temp2.at(i * 2), std::stod(temp2.at((i * 2) + 1).c_str())));
		}
		temp2.clear();

		mylib::readFile(evntbase, temp1);
		formString(temp1, temp2);
		temp1.clear();

		if ((temp2.size() % evnts.size()) != 0)
		{
			std::cout << "Error in " << evntbase << ". Element count mismatch." << std::endl;
			return 0;
		}
		else
		{
			for (int i = 0; i < (temp2.size() / evnts.size()); i++)
			{
				for (int o = 0; o < evnts.size(); o++)
					evnts.at(o).addMea(std::stod(temp2.at((i * evnts.size()) + o).c_str()));
			}
			temp2.clear();

			mylib::readFile(evntest, temp1);
			formString(temp1, temp2);
			temp1.clear();

			if ((temp2.size() % evnts.size()) != 0)
			{
				std::cout << "Error in " << evntest << ". Element count mismatch." << std::endl;
				return 0;
			}
			else
			{
				for (int i = 0; i < (temp2.size() / evnts.size()); i++)
				{
					for (int o = 0; o < evnts.size(); o++)
						evnts.at(o).addTest(std::stod(temp2.at((i * evnts.size()) + o).c_str()));
				}
				temp2.clear();

				display(evnts);
			}
		}
	}
	system("pause");
	return 0;
}

