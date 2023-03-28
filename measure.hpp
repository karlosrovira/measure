#ifndef MEASURE_HPP
#define MEASURE_HPP

#include <string>

namespace measure {
const double GRAMS_PER_POUND = 453.6;
const double INCHES_PER_METER = 1.0 / 0.0254;
const double SECONDS_PER_MINUTE = 60.0;
  
enum modifier_t {
  NONE,
  KILO, MEGA,
  MILLI, MICRO
};

enum mass_t {
  GRAM, POUND
};
  
enum distance_t {
  METER, INCH, FOOT, YARD
};

enum time_t {
  SECOND, MINUTE, HOUR
};
  
typedef int power_t;
  
struct unit
{
  modifier_t mass_modifier;
  mass_t     mass_unit;
  power_t    mass_power;
  
  modifier_t distance_modifier;
  distance_t distance_unit;
  power_t    distance_power;

  modifier_t time_modifier;
  time_t     time_unit;
  power_t    time_power;

  unit()
    : mass_modifier(NONE), mass_unit(GRAM), mass_power(0),
      distance_modifier(NONE), distance_unit(METER), distance_power(0),
      time_modifier(NONE), time_unit(SECOND), time_power(0)
  {}
};

/**
 * A measure is saved by default in g * m * s
 */
typedef double measure_t;
  
measure_t convert_from(double val, const unit& u);
double convert_to(measure_t m, const unit& u);

/**
 * Express measure @b m in units @b u as a string.
 */
std::string to_string(measure_t m, const unit& u);
} // namespace measure 

#endif	// !MEASURE_HPP
