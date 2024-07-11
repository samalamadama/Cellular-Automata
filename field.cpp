#include "field.hpp"
#include <algorithm>

bool Field::evolve()
{
  boost::dynamic_bitset<> const initial_state{field_};
  bool success{true};
  int neighbourhood_type;
  for (int i = 0; i != (int)field_.size() && success; ++i){
    if(i==0){
    neighbourhood_type = (int)(initial_state[i+1]<<2|initial_state[i]<<1|initial_state[initial_state.size()-1]);
    }else{
      if(i==(int)initial_state.size()-1){
      neighbourhood_type = (int)(initial_state[0]<<2|initial_state[i]<<1|initial_state[i-1]);
      }else{
        neighbourhood_type = (int)(initial_state[i+1]<<2|initial_state[i]<<1|initial_state[i-1]);
      }
    }
    switch((int)neighbourhood_type){
      // when the neighbourhood is in the state 000
        case 0:
        field_[i] = rule_[0];
        break;
      // 001
        case 1:
        field_[i] = rule_[1];
        break;
      // 010
        case 2:
        field_[i] = rule_[2];
        break;
      // 011
        case 3:
        field_[i] = rule_[3];
        break;
      // 100
        case 4:
        field_[i] = rule_[4];
        break;
      // 101
        case 5:
        field_[i] = rule_[5];
        break;
      // 110
        case 6:
        field_[i] = rule_[6];
        break;
      // 111
        case 7:
        field_[i] = rule_[7];
        break;
        default:
        success = false;
        break;
    }
  }
  return success;
}