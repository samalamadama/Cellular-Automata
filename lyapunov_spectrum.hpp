#include <Eigen/Dense>
#include "boost/dynamic_bitset.hpp"
#include "field.hpp"
#include <iostream>

Eigen::Matrix<unsigned long long int, Eigen::Dynamic, Eigen::Dynamic> jacobian(Field const& field) {
    int dimension = (int)field.get_field().size();
    Eigen::Matrix<unsigned long long int, Eigen::Dynamic, Eigen::Dynamic> jacob(dimension, dimension);
    Field evolved = field;
    evolved.evolve();
    for(int i=0; i!=dimension; ++i){
        Field damaged = field;
        damaged.flip(i);
        damaged.evolve();
        boost::dynamic_bitset<> difference = damaged.get_field() ^ evolved.get_field();
        for(int j=0; j!=dimension; ++j){
            jacob(j, i) = difference[j];
        }
    }
    return jacob;    
}

std::vector<double> lyapunov_spectrum(boost::dynamic_bitset<> rule){
    int n_cells{500};
    int n_evolutions{500};
    int n_iterations{40};
    std::vector<double> spectrum;
    spectrum.reserve(n_cells*n_iterations);

    for(int iteration=0; iteration!=n_iterations; ++iteration){
    Field field{n_cells, -1, rule};
    Eigen::Matrix<unsigned long long int, Eigen::Dynamic, Eigen::Dynamic> Y = Eigen::Matrix<unsigned long long int, Eigen::Dynamic, Eigen::Dynamic>::Identity(n_cells, n_cells);
    for(int i=0; i!=n_evolutions&&(Y.maxCoeff()<ULLONG_MAX/2); ++i){
        Y = jacobian(field)*Y;
        field.evolve();
    }

    Eigen::MatrixXd L = (Y * Y.transpose()).cast<double>();
    Eigen::SelfAdjointEigenSolver<Eigen::MatrixXd> eigensolver(L);
    if(eigensolver.info() != Eigen::Success) throw std::runtime_error("invalid eigensolver");
      for(int i=0; i!= n_cells; ++i){
      spectrum.push_back(std::log(eigensolver.eigenvalues()(i))/(2*n_evolutions));
      }

      std::cout<<(iteration+1)*100/n_iterations<<"%\n";
    }
    return spectrum;
}