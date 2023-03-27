#include "measure.hpp"

#include <iostream>

using namespace std;
using namespace measurement;

int main()
{
  measure<double> m(123.4);
  m.set_time_power(-2);
  m.set_distance_power(1);
  m.set_mass_power(1);
  m.set_mass_modifier(measurement::measure<double>::KILO);
  cout << "Printing 123.4kg_m_s-2:\n";
  cout << "  " << m << "\n";
  return 0;
}
