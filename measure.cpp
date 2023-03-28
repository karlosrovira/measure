#include "measure.hpp"

#include <cassert>
#include <cmath>
#include <functional>

namespace measure {
double _modifier_factor(modifier_t mod)
{
  switch (mod)
    {
    case NONE:
      return 1.0;
    case KILO:
      return 1000.0;
    case MILLI:
      return 0.001;

    default:
      assert(false);
    }
}

double _mass_factor(mass_t uni)
{
  switch (uni)
    {
    case GRAM:
      return 1.0;
    case POUND:
      return GRAMS_PER_POUND;

    default:
      assert(false);
    }
}
  
double _distance_factor(distance_t uni)
{
  switch (uni)
    {
    case METER:
      return 1.0;
    case INCH:
      return 1 / INCHES_PER_METER;

    default:
      assert(false);
    }
}

double _time_factor(time_t uni)
{
  switch (uni)
    {
    case SECOND:
      return 1.0;
    case MINUTE:
      return SECONDS_PER_MINUTE;

    default:
      assert(false);
    }
}
  
double _power_factor(double factor, power_t pwr)
{
  return pow(factor, pwr);
}

double _unit_factor(const unit& u)
{
  return (_power_factor(_modifier_factor(u.distance_modifier) * _distance_factor(u.distance_unit), u.distance_power)
	  * _power_factor(_modifier_factor(u.mass_modifier) * _mass_factor(u.mass_unit), u.mass_power)
	  * _power_factor(_modifier_factor(u.time_modifier) * _time_factor(u.time_unit), u.time_power));
}

std::string _to_string(modifier_t mod)
{
  switch (mod)
    {
    case NONE:
      return "";
    case KILO:
      return "k";
    case MILLI:
      return "m";
	  
    default:
      assert(false);
    }
}

std::string _to_string(mass_t uni)
{
  switch (uni)
    {
    case GRAM:
      return "g";
    case POUND:
      return "lb";

    default:
      assert(false);
    }
}

std::string _to_string(distance_t uni)
{
  switch (uni)
    {
    case METER:
      return "m";
    case INCH:
      return "in";

    default:
      assert(false);
    }
}

std::string _to_string(time_t uni)
{
  switch (uni)
    {
    case SECOND:
      return "s";
    case MINUTE:
      return "min";

    default:
      assert(false);
    }
}
  
std::string _to_string(const unit& u)
{
  std::string result = "_";

  if (u.mass_power != 0)
    {
      result += _to_string(u.mass_modifier);
      result += _to_string(u.mass_unit);
      if (u.mass_power != 1)
	result += std::to_string(u.mass_power);
    }
  if (u.distance_power != 0)
    {
      if (u.mass_power != 0)
	result += ".";
      result += _to_string(u.distance_modifier);
      result += _to_string(u.distance_unit);
      if (u.distance_power != 1)
	result += std::to_string(u.distance_power);
    }
  if (u.time_power != 0)
    {
      if (u.mass_power != 0 or u.distance_power != 0)
	result += ".";
      result += _to_string(u.time_modifier);
      result += _to_string(u.time_unit);
      if (u.time_power != 1)
	result += std::to_string(u.time_power);
    }

  return result;
}
  
measure_t convert_from(double val, const unit &u)
{
  return val * _unit_factor(u);
}

double convert_to(measure_t m, const unit& u)
{
  return m / _unit_factor(u);
}

std::string to_string(measure_t m, const unit& u)
{
  return std::to_string(convert_to(m, u)) + _to_string(u);
}
} // namespace measure 
