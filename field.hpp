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
  Field(int length, boost::dynamic_bitset<> rule) : field_(length), rule_{rule} {}


  Field(int length, int n_alive, boost::dynamic_bitset<> rule) : Field(length, rule)
  {
    if (n_alive < -1 || n_alive > length)
      throw std::out_of_range("number of alive cell selected invalid");
    RandomIntGenerator random_position_{0, length-1};
    RandomIntGenerator random_status_{0, 1};
    if(n_alive==-1){
      for(int i=0; i!=length; ++i){
        field_[i] = random_status_.get();
      }
    }else{
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
  }

  Field(Field const& field_to_copy) : field_{field_to_copy.get_field()}, rule_{field_to_copy.get_rule()}{}

  void evolve();

  int get_neighborhood_type(int position) const;

  boost::dynamic_bitset<> const &get_field() const { return field_; }

  void set_alive(int position)
  { 
    field_[position]=1;
  }

  void set_dead(int position){
    field_[position]=0;
  }

  void flip(int position){
    field_[position] = !field_[position];
  }

  boost::dynamic_bitset<> const &get_rule() const {
    return rule_;
  }

private:
  boost::dynamic_bitset<> field_;
  const boost::dynamic_bitset<> rule_;
};

#endif