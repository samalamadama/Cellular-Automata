#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include "TileMap.hpp"
#include "field.hpp"
#include "texture.hpp"
#include "bit_matrix.hpp"
#include <iostream>
#include "boost/dynamic_bitset.hpp"
#include <cmath>

int main()
{
  try
  {
    int screen_duration_in_seconds = 3;

    sf::Vector2i const screenDimensions{500, 500};
    sf::Vector2i fieldDimentions{0, 0};
    sf::Vector2i tileDimentions{0, 0};
    int n_cells{0};
    boost::dynamic_bitset<> rule {00000000};
    std::string rule_in_strings;

    std::cout<<"Insert rule"<<'\n';
    std::cin>>rule;
    if (!std::cin.good())
    {
      throw std::runtime_error("rule not acceptable");
    }
    to_string(rule, rule_in_strings);

    std::cout << "Inserire numero di cellule" << '\n';
    std::cin >> fieldDimentions.x;
    if (!std::cin.good())
    {
      throw std::runtime_error("error in cell numeber selection");
    }

    std::cout << "Inserire numero di iterazioni" << '\n';
    std::cin >> fieldDimentions.y;
    if (!std::cin.good())
    {
      throw std::runtime_error("error in iteration selection");
    }
    std::cout << "Inserire numero di celle vive" << '\n';
    std::cin >> n_cells;
    if (!std::cin.good())
    {
      throw std::runtime_error("error in number of alive cells selection");
    }

    int iteration_per_second{fieldDimentions.y/screen_duration_in_seconds};
    Bit_Matrix log_book(fieldDimentions.y, fieldDimentions.x);

    tileDimentions = CalculateTileDimensions(screenDimensions, fieldDimentions);

    sf::RenderWindow window(sf::VideoMode(tileDimentions.x * fieldDimentions.x,
                                          tileDimentions.y * fieldDimentions.y),
                            "cellular automata, rule " + rule_in_strings,
                            sf::Style::Titlebar | sf::Style::Close);
    window.setPosition(sf::Vector2i(100, 30));

    Field field{fieldDimentions.x, n_cells, rule};
    Field field_damaged{field};
    field_damaged.flip(std::floor(fieldDimentions.x/2));
    TileMap tiles;

    // chances of improval here, could make the clock independent of the fps part
    sf::Clock clock;
    sf::Time elapsed;

    bool game_is_on{true};
    int iteration=0;

    // also could check if there where any event and if there weren't not redraw everything
    while (window.isOpen())
    {
      //sf::Vector2i mouseTile =
      //    CalculateTile(sf::Mouse::getPosition(window), tileDimentions);

      sf::Event event;
      while (window.pollEvent(event))
      {
        switch (event.type)
        {
        case sf::Event::Closed:
          window.close();
          break;
        case sf::Event::MouseButtonPressed:
          switch (event.mouseButton.button)
          {
          case sf::Mouse::Right:
            break;
          default:
            break;
          }
          break;
        default:
          break;
        }
      }

      elapsed = clock.getElapsedTime();
      if (game_is_on && elapsed > sf::milliseconds(1000 / iteration_per_second))
      {
        field.evolve();
        field_damaged.evolve();
        if(iteration<fieldDimentions.y)
        log_book.set_row(iteration%log_book.get_height()+1, field.get_field());
        ++iteration;
        clock.restart();
        if (!tiles.load(tileDimentions, TextureMatrix(log_book)))
          return -1;
        if(iteration%10==0){
        window.clear();
        window.draw(tiles);
        window.display();
        }
      }
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
