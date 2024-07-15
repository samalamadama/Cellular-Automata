#include "field.hpp"
#include "lyapunov_spectrum.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include <cmath>
#include <climits>
#include <fstream>

int main(){
    try{
    int cell_alive{0};
    int cell_number{0};
    int number_of_evolutions{0};

    int rule_decimal;

    std::cout<<"Insert rule"<<'\n';
    std::cin>>rule_decimal;
    if (!std::cin.good())
    {
      throw std::runtime_error("rule not acceptable");
    }
    boost::dynamic_bitset<> rule(8, rule_decimal);

    std::ofstream file{"/mnt/c/Users/andre/Desktop/uni/2023_2024/sistemi_complessi/"+std::to_string(rule_decimal)+".txt"};



    std::cout << "Inserire numero di cellule" << '\n';
    std::cin >> cell_number;
    if (!std::cin.good())
    {
      throw std::runtime_error("error in cell numeber selection");
    }

    std::cout << "Inserire numero di iterazioni" << '\n';
    std::cin >> number_of_evolutions;
    if (!std::cin.good())
    {
      throw std::runtime_error("error in iteration selection");
    }
    std::cout << "Inserire numero di celle vive" << '\n';
    std::cin >> cell_alive;
    if (!std::cin.good())
    {
      throw std::runtime_error("error in number of alive cells selection");
    }

    Field field{cell_number, cell_alive, rule};
    int counter{0};

    Eigen::Matrix<unsigned long long int, Eigen::Dynamic, Eigen::Dynamic> Y = Eigen::Matrix<unsigned long long int, Eigen::Dynamic, Eigen::Dynamic>::Identity(cell_number, cell_number);
    for(int i=0; i!=number_of_evolutions&&(Y.maxCoeff()<ULLONG_MAX/2); ++i){
        Y = jacobian(field)*Y;
        ++counter;
        field.evolve();
    }
    std::cout<<'\n';

    Eigen::MatrixXd L = (Y * Y.transpose()).cast<double>();
    Eigen::SelfAdjointEigenSolver<Eigen::MatrixXd> eigensolver(L);
    if(eigensolver.info() != Eigen::Success) throw std::runtime_error("invalid eigensolver");
    if(file.is_open()){
      for(int i=0; i!= cell_number; ++i){
      file<<std::log(eigensolver.eigenvalues()(i))/(2*floor(cell_number/2))<<'\n';
      }
      file.close();
    }
    
    }
    catch (std::runtime_error &error)
  {
    std::cout << error.what() << '\n';
    return EXIT_FAILURE;
  }
  catch (std::out_of_range &error)
  {
    std::cout << error.what() << '\n';
    return EXIT_FAILURE; 
  }
  catch (...)
  {
    std::cout << "unknown exception occurred";
    return EXIT_FAILURE;
  }
}