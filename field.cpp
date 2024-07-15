#include "field.hpp"
#include <algorithm>

void Field::evolve()
{
  Field const initial_state{*this};
  for (int i = 0; i != (int)field_.size(); ++i){
    field_[i] = rule_[initial_state.get_neighborhood_type(i)];
  }
}

int Field::get_neighborhood_type(int position) const{
  int neighborhood_type;
    if(position==0){
    neighborhood_type = (int)(field_[position+1]<<2|field_[position]<<1|field_[field_.size()-1]);
    }else{
      if(position==(int)field_.size()-1){
      neighborhood_type = (int)(field_[0]<<2|field_[position]<<1|field_[position-1]);
      }else{
        neighborhood_type = (int)(field_[position+1]<<2|field_[position]<<1|field_[position-1]);
      }
    }
    return neighborhood_type;
}