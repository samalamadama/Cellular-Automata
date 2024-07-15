#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include "field.hpp"
#include <iostream>
#include "lyapunov_spectrum.hpp"
#include "boost/dynamic_bitset.hpp"
#include <cmath>

int main(){
    boost::dynamic_bitset<> rule(8, 150);
    Field field(20, 0, rule);
    auto jacob = jacobian(field);
    Eigen::SelfAdjointEigenSolver<Eigen::MatrixXd> eigensolver(jacob.cast<double>());

    for (int i=0; i!=5; ++i){
        field.evolve();
        jacob = jacobian(field)*jacob;
            }

    Eigen::SelfAdjointEigenSolver<Eigen::MatrixXd> eigensolver2(jacob.cast<double>());
    for(int i=0; i!= jacob.diagonalSize(); ++i){
        std::cout<<std::log(eigensolver2.eigenvalues()(i))/6<<"   "<<std::log(eigensolver.eigenvalues()(i))<<'\n';
        } 
}