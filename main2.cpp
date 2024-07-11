#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include "field.hpp"
#include "bit_matrix.hpp"
#include <iostream>

int main(){
    Field field(100, 50, std::bitset<8>("01101110"));
    std::cout<<"n iterasions"<<'\n';
    int n_iterations;
    std::cin>>n_iterations;
    Bit_Matrix matrix(n_iterations, 100);
    for(int i=0; i!= matrix.get_height(); ++i){
        matrix.set_row(i+1, field.get_field());
        field.evolve();
    }
    for(int i=0; i!= matrix.get_height(); ++i){
        std::cout<<matrix.get_row(i+1)<<'\n';
    }
}