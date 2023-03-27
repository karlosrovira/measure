#pragma once

#include <algorithm>
#include <cassert>
#include <cmath>
#include <ostream>
#include <unordered_map>

namespace measurement {
/**
 * A measure is a value with a unit.
 */
template <typename T>
class measure
{
public:
  typedef T value_type;
  typedef int power_type;
  
  enum modifier_type {
    NONE = 0, KILO = 1, MEGA = 2, MILLI = -1, MICRO = -2
  };
  
  enum distance_type {
    METER, INCH
  };

  enum mass_type {
    GRAM, POUND
  };

  enum time_type {
    SECOND, MINUTE, HOUR
  };
  
  measure(value_type __v = 0.0)
  {
    _value = __v;
    _distance = {METER, NONE, 0};
    _mass = {GRAM, NONE, 0};
    _time = {SECOND, NONE, 0};    
  }

  // Access
  value_type value() const { return _value; }

  power_type distance_power() const { return std::get<2>(_distance); }
  modifier_type distance_modifier() const { return std::get<1>(_distance); }
  distance_type distance_unit() const { return std::get<0>(_distance); }

  power_type mass_power() const { return std::get<2>(_mass); }
  modifier_type mass_modifier() const { return std::get<1>(_mass); }
  mass_type mass_unit() const { return std::get<0>(_mass); }

  power_type time_power() const { return std::get<2>(_time); }
  modifier_type time_modifier() const { return std::get<1>(_time); }
  time_type time_unit() const { return std::get<0>(_time); }

  // Setting
  void set_value(value_type __v) { _value = __v; }
  
  void set_distance_power(power_type __p)
  {
    const auto [ u, m, _ ] = _distance;
    _distance = {u, m, __p};
  }
  
  void set_mass_power(power_type __p)
  {
    const auto [ u, m, _ ] = _mass;
    _mass = {u, m, __p};
  }

  void set_time_power(power_type __p)
  {
    const auto [ u, m, _ ] = _time;
    _time = {u, m, __p};
  }

  void set_distance_modifier(modifier_type __m)
  {
    const auto [ u, _, p ] = _distance;
    _distance = {u, __m, p};
  }
  
  void set_mass_modifier(modifier_type __m)
  {
    const auto [ u, _, p ] = _mass;
    _mass = {u, __m, p};
  }

  void set_time_modifier(modifier_type __m)
  {
    const auto [ u, _, p ] = _time;
    _time = {u, __m, p};
  }      

  void set_distance_unit(distance_type __u)
  {
    const auto [ _, m, p ] = _distance;
    _distance = {__u, m, p};
  }
  
  void set_mass_unit(mass_type __u)
  {
    const auto [ _, m, p ] = _mass;
    _mass= {__u, m, p};
  }

  void set_time_unit(time_type __u)
  {
    const auto [ _, m, p ] = _time;
    _time = {__u, m, p};
  }      
  
  // Operations
  void convert_distance_modifier(modifier_type __to)
  {
    int base = distance_modifier() - __to;
    _value *= pow(1000, base);
    set_distance_modifier(__to);
  }

  void convert_mass_modifier(modifier_type __to)
  {
    int base = mass_modifier() - __to;
    _value *= pow(1000, base);
    set_mass_modifier(__to);
  }

  void convert_time_modifier(modifier_type __to)
  {
    int base = time_modifier() - __to;
    _value *= pow(1000, base);
    set_time_modifier(__to);
  }
  
  void convert_distance_unit(distance_type __to)
  {
  }

  void convert_mass_unit(mass_type __to)
  {
  }

  void convert_time_unit(time_type __to)
  {
  }

private:
  value_type _value;
  std::tuple<distance_type, modifier_type, power_type> _distance;
  std::tuple<mass_type, modifier_type, power_type>     _mass;
  std::tuple<time_type, modifier_type, power_type>     _time;  
};
  
template<typename T>
measure<T> make_meter(double v = 0.0)
{
  return {};
}

template<typename T>
measure<T> make_kilogram(double v = 0.0)
{
  return {};
}

// Arithmetic Operations. Keep the units of the left in case of sum/take.
// They all require that powers are the same for the respective unit.

template <typename T>
measure<T> sumortake(const measure<T>& m1, const measure<T>& m2, bool sum)
{
  assert(m1.mass_power() == m2.mass_power());
  assert(m1.distance_power() == m2.distance_power());
  assert(m1.time_power() == m2.time_power());
  
  measure<T> result = m1, aux = m2;
  
  aux.convert_mass_modifier(m1.mass_modifier());
  aux.convert_distance_modifier(m1.distance_modifier());
  aux.convert_time_modifier(m1.time_modifier());
  aux.convert_mass_unit(m1.mass_unit());
  aux.convert_distance_unit(m1.distance_unit());
  aux.convert_time_unit(m1.time_unit());
  if (sum)
    result.set_value(result.value() + aux.value());
  else
    result.set_value(result.value() - aux.value());
  
  return result;
}
  
template <typename T>
measure<T> operator+(const measure<T>& m1, const measure<T>& m2)
{
  return sumortake(m1, m2, true);
}

template <typename T>
measure<T> operator-(const measure<T>& m1, const measure<T>& m2)
{
  return sumortake(m1, m2, false);
}
  
// Printing

template<typename T>
void print(std::ostream& o, const typename measure<T>::modifier_type m)
{
  switch(m)
    {
    case measure<T>::NONE:
      break;
    case measure<T>::KILO:
      o << "k";
      break;
    case measure<T>::MEGA:
      o << "M";
      break;
    case measure<T>::MILLI:
      o << "m";
      break;
    case measure<T>::MICRO:
      o << "u";
      break;    
      
    default:
      assert(false);
    }
}

template<typename T>
void print(std::ostream& o, const typename measure<T>::mass_type t)
{
  switch(t)
    {
    case measure<T>::GRAM:
      o << "g";
      break;
    case measure<T>::POUND:
      o << "lb";
      break;

    default:
      assert(false);
    }
}

template<typename T>
void print(std::ostream& o, const typename measure<T>::distance_type t)
{
  switch(t)
    {
    case measure<T>::METER:
      o << "m";
      break;
    case measure<T>::INCH:
      o << "in";
      break;

    default:
      assert(false);
    }
}

template<typename T>
void print(std::ostream& o, const typename measure<T>::time_type t)
{
  switch(t)
    {
    case measure<T>::SECOND:
      o << "s";
      break;
    case measure<T>::MINUTE:
      o << "min";
      break;      
    case measure<T>::HOUR:
      o << "h";
      break;

    default:
      assert(false);
    }
}
  
template<typename T>
std::ostream& operator<<(std::ostream& o, const measure<T>& m)
{
  o << m.value();
  if (m.mass_power() != 0)
    {
      print<T>(o, m.mass_modifier());
      print<T>(o, m.mass_unit());
      if (m.mass_power() != 1)
	o << m.mass_power();

      if (m.distance_power() != 0)
	o << "_";
    }
  if (m.distance_power() != 0)
    {
      print<T>(o, m.distance_modifier());
      print<T>(o, m.distance_unit());
      if (m.distance_power() != 1)
	o << m.distance_power();

      if (m.time_power() != 0)
	o << "_";
    }
  if (m.time_power() != 0)
    {
      print<T>(o, m.time_modifier());
      print<T>(o, m.time_unit());
      if (m.time_power() != 1)
	o << m.time_power();
    }
  return o;
}  
} // namespace measurement
