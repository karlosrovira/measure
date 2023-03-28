#include "measure.cpp"
#include "measure.hpp"

#include <gtest/gtest.h>

using namespace measure;

void test_range(double tested, double other)
{
  EXPECT_TRUE(tested <= other + tested / 2000 and other - tested / 2000 <= tested) << "Got: " << tested;
}

TEST(measure, convert_from0)
{
  EXPECT_EQ(convert_from(10.0, unit{}), 10.0);
}

TEST(measure, convert_from_kg)
{
  unit u;
  u.mass_power = 1;
  u.mass_modifier = KILO;
  EXPECT_EQ(convert_from(10.0, u), 10.0e3);
}

TEST(measure, convert_from_kg2)
{
  unit u;
  u.mass_power = 2;
  u.mass_modifier = KILO;
  EXPECT_EQ(convert_from(10.0, u), 10.0e6);
}

TEST(measure, convert_from_mm)
{
  unit u;
  u.distance_power = 1;
  u.distance_modifier = MILLI;
  EXPECT_EQ(convert_from(10.0, u), 10.0e-3);
}

TEST(measure, convert_from_inch)
{
  unit u;
  u.distance_power = 1;
  u.distance_unit = INCH;
  EXPECT_EQ(convert_from(10.0, u), 10.0 / INCHES_PER_METER);
}

TEST(measure, convert_from_inch2)
{
  unit u;
  u.distance_power = 2;
  u.distance_unit = INCH;
  test_range(convert_from(10.0, u), 10.0 / (INCHES_PER_METER * INCHES_PER_METER));
}

TEST(measure, convert_from_pound)
{
  unit u;
  u.mass_power = 1;
  u.mass_unit = POUND;
  test_range(convert_from(10.0, u), 10.0 * GRAMS_PER_POUND);
}

TEST(measure, convert_from_pound2)
{
  unit u;
  u.mass_power = 2;
  u.mass_unit = POUND;
  test_range(convert_from(10.0, u), 10.0 * (GRAMS_PER_POUND * GRAMS_PER_POUND));
}

TEST(measure, convert_from_minute)
{
  unit u;
  u.time_power = 1;
  u.time_unit = MINUTE;
  test_range(convert_from(10.0, u), 10.0 * SECONDS_PER_MINUTE);
}

TEST(measure, convert_from_second_2)
{
  unit u;
  u.time_power = -2;
  test_range(convert_from(10.0, u), 10.0);
}

TEST(measure, convert_from_newton)
{
  unit u;

  u.mass_modifier = KILO;
  //u.mass_unit = GRAM;
  u.mass_power = 1;
  //u.distance_modifier = NONE;
  //u.distance_unit = METER;
  u.distance_power = 1;
  //u.time_modifier = NONE;
  //u.time_unit = SECOND;
  u.time_power = -2;

  test_range(convert_from(10.0, u), 10.0e3);
}

TEST(measure, to_string)
{
  unit u;
  measure_t m;
  
  u.mass_modifier = KILO;
  u.mass_power = 1;
  u.distance_power = 1;
  u.time_power = -2;

  m = convert_from(123.4, u);
  
  EXPECT_EQ(to_string(m, u), "123.400000_kg.m.s-2");
}
