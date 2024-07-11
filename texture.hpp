#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include <cmath>

#include "matrix.hpp"
#include "bit_matrix.hpp"
#include "field.hpp"

//finds the tile relative to a position on the screen
sf::Vector2i CalculateTile(sf::Vector2i position, sf::Vector2i tileDimentions);

//Returns a matrix of integers, each of which represents the status of the tile (i, j). 
//This is then use to select the correct texture for each tile
Matrix<int> TextureMatrix(Bit_Matrix matrix);

//based on the dimensions of the screen it calculates the dimension of the tiles
sf::Vector2i CalculateTileDimensions(sf::Vector2i const& screenDimensions, sf::Vector2i const& fieldDimentions);
#endif