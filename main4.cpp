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
    int rule_decimal;

    std::cout<<"Insert rule"<<'\n';
    std::cin>>rule_decimal;
    if (!std::cin.good())
    {
      throw std::runtime_error("rule not acceptable");
    }
    boost::dynamic_bitset<> rule(8, rule_decimal);

    std::ofstream file{"/mnt/c/Users/andre/Desktop/uni/2023_2024/sistemi_complessi/"+std::to_string(rule_decimal)+".txt"};

    if(file.is_open()){
        std::vector<double> spectrum = lyapunov_spectrum(rule);
        std::ostream_iterator<double> output_iterator(file, "\n");
        std::copy(std::begin(spectrum), std::end(spectrum), output_iterator);
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