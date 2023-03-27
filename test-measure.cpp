#include "measure.hpp"

#include <gtest/gtest.h>

using measurement::measure;

constexpr auto METER = measure<float>::METER;
constexpr auto INCH = measure<float>::INCH;

constexpr auto SECOND = measure<float>::SECOND;
constexpr auto MINUTE = measure<float>::MINUTE;

constexpr auto GRAM = measure<float>::GRAM;
constexpr auto POUND = measure<float>::POUND;

constexpr auto NONE = measure<float>::NONE;
constexpr auto KILO = measure<float>::KILO;

TEST(measure, ConstructorBase)
{
  measure<float> tested;
}

TEST(measure, value)
{
  measure<float> tested;
  EXPECT_EQ(tested.value(), 0.0);
}

// Access

TEST(measure, value_10)
{
  measure<float> tested(10.0);
  EXPECT_EQ(tested.value(), 10.0);
}

// distance
TEST(measure, distance_power)
{
  measure<float> tested;
  EXPECT_EQ(tested.distance_power(), 0);
}

TEST(measure, distance_modifier)
{
  measure<float> tested;
  EXPECT_EQ(tested.distance_modifier(), NONE);
}

TEST(measure, distance_unit)
{
  measure<float> tested;
  EXPECT_EQ(tested.distance_unit(), METER);
}

// mass
TEST(measure, mass_power)
{
  measure<float> tested;
  EXPECT_EQ(tested.mass_power(), 0);
}

TEST(measure, mass_modifier)
{
  measure<float> tested;
  EXPECT_EQ(tested.mass_modifier(), NONE);
}

TEST(measure, mass_unit)
{
  measure<float> tested;
  EXPECT_EQ(tested.mass_unit(), GRAM);
}

// time
TEST(measure, time_power)
{
  measure<float> tested;
  EXPECT_EQ(tested.time_power(), 0);
}

TEST(measure, time_modifier)
{
  measure<float> tested;
  EXPECT_EQ(tested.time_modifier(), NONE);
}

TEST(measure, time_unit)
{
  measure<float> tested;
  EXPECT_EQ(tested.time_unit(), SECOND);
}

// Setters

TEST(measure, set_value)
{
  measure<float> tested;
  tested.set_value(10.0);
  EXPECT_EQ(tested.value(), 10.0);
}

// distance 
TEST(measure, set_distance_unit)
{
  measure<float> tested;
  tested.set_distance_unit(INCH);
  EXPECT_EQ(tested.distance_unit(), INCH);
}

TEST(measure, set_distance_modifier)
{
  measure<float> tested;
  tested.set_distance_modifier(KILO);
  EXPECT_EQ(tested.distance_modifier(), KILO);
}

TEST(measure, set_distance_power)
{
  measure<float> tested;
  tested.set_distance_power(2);
  EXPECT_EQ(tested.distance_power(), 2);
}

// mass 
TEST(measure, set_mass_unit)
{
  measure<float> tested;
  tested.set_mass_unit(POUND);
  EXPECT_EQ(tested.mass_unit(), POUND);
}

TEST(measure, set_mass_modifier)
{
  measure<float> tested;
  tested.set_mass_modifier(KILO);
  EXPECT_EQ(tested.mass_modifier(), KILO);
}

TEST(measure, set_mass_power)
{
  measure<float> tested;
  tested.set_mass_power(2);
  EXPECT_EQ(tested.mass_power(), 2);
}

// time 
TEST(measure, set_time_unit)
{
  measure<float> tested;
  tested.set_time_unit(MINUTE);
  EXPECT_EQ(tested.time_unit(), MINUTE);
}

TEST(measure, set_time_modifier)
{
  measure<float> tested;
  tested.set_time_modifier(KILO);
  EXPECT_EQ(tested.time_modifier(), KILO);
}

TEST(measure, set_time_power)
{
  measure<float> tested;
  tested.set_time_power(2);
  EXPECT_EQ(tested.time_power(), 2);
}

// convert 
TEST(measure, convert_distance_modifier)
{
  measure<float> tested(10.0);
  tested.convert_distance_modifier(KILO);
  EXPECT_EQ(tested.distance_modifier(), KILO);
  //EXPECT_EQ(tested.value(), 0.01); fails for some reason
  EXPECT_TRUE(tested.value() <= 0.01 and tested.value() >= 0.00999);
}

TEST(measure, convert_mass_modifier)
{
  measure<float> tested(10.0);
  tested.convert_mass_modifier(KILO);
  EXPECT_EQ(tested.mass_modifier(), KILO);
  //EXPECT_EQ(tested.value(), 0.01); fails for some reason
  EXPECT_TRUE(tested.value() <= 0.01 and tested.value() >= 0.00999);
}

TEST(measure, convert_time_modifier)
{
  measure<float> tested(10.0);
  tested.convert_time_modifier(KILO);
  EXPECT_EQ(tested.time_modifier(), KILO);
  //EXPECT_EQ(tested.value(), 0.01); fails for some reason
  EXPECT_TRUE(tested.value() <= 0.01 and tested.value() >= 0.00999);
}

TEST(measure, Sum)
{
  measure<float> left, right, result;
  left.set_mass_power(1);
  left.set_value(100.0);	// 100.0g
  right.set_mass_power(1);
  right.set_value(10.0);
  right.set_mass_modifier(KILO); // 10.0kg
  result = left + right;
  EXPECT_EQ(result.value(), 10100.0);
  EXPECT_EQ(result.mass_power(), 1);
  EXPECT_EQ(result.mass_modifier(), NONE);
}

TEST(measure, Take)
{
  measure<float> left, right, result;
  left.set_mass_power(1);
  left.set_value(100.0);	// 100.0g
  right.set_mass_power(1);
  right.set_value(10.0);
  right.set_mass_modifier(KILO); // 10.0kg
  result = left - right;
  EXPECT_EQ(result.value(), -9900.0);
  EXPECT_EQ(result.mass_power(), 1);
  EXPECT_EQ(result.mass_modifier(), NONE);
}
