#ifndef FIELD_HPP
#define FIELD_HPP

#include <algorithm>
#include <random>
#include <stdexcept>

#include "boost/dynamic_bitset.hpp"

class RandomIntGenerator
{
public:
  RandomIntGenerator(int lower, int upper)
      : distribution(lower, upper), engine(device()) {}

  int get() { return distribution(engine); }

private:
  std::random_device device;
  std::uniform_int_distribution<int> distribution;
  std::default_random_engine engine;
};

class Field
{
public:
  Field(int length, std::bitset<8> rule) : field_(length), rule_{rule} {}

  Field(int length, int n_alive, std::bitset<8> rule) : Field(length, rule)
  {
    if (n_alive < 0 || n_alive > length)
      throw std::out_of_range("number of alive cell selected invalid");
    RandomIntGenerator random_position_{0, length-1};
    while (n_alive != 0)
    {
      int position = random_position_.get();
      if (!field_[position])
      {
        --n_alive;
        field_[position]=1;
      }
    }
  }

  bool evolve();

  boost::dynamic_bitset<> const &get_field() const { return field_; }

  void set_alive(int position)
  {
    field_[position]=1;
  }

private:
  boost::dynamic_bitset<> field_;
  const std::bitset<8> rule_;
};

#endif