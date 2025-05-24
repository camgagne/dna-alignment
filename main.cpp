// Copyright 2025 Cameron Gagne and Ryan Greaney

#include <iostream>
#include "EDistance.hpp"
#include <SFML/System.hpp>

int main(int argc, char *argv[]) {
  sf::Clock clock;
  std::string str1, str2;
  std::cin >> str1;
  std::cin >> str2;
  EDistance* eDis = new EDistance(str1, str2);
  std::cout << "Edit distance = " << eDis->optDistance() << std::endl;
  std::cout <<  eDis->alignment() << std::endl;
  sf::Time t = clock.getElapsedTime();
  std::cout << "Execution time is " << t.asSeconds() << " seconds" << std::endl;
  return 0;
}
