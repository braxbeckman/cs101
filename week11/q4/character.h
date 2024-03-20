#pragma once
#include <string>
#include <vector>

class character
{
public:
  character();
  int rollOneStat();
  void allocateStats();
  void rollStats();

private:
  std::string build{"Commoner"};
  int health{5};

  std::vector<int> statSpread{};

  // order for stats goes Strength, Dexterity, Consitution, Intelligence, Wisdom, Charisma
  std::vector<int> stats{1, 1, 1, 1, 1, 1};
  int str{1};
  int dex{1};
  int con{1};
  int intl{1};
  int wis{1};
  int cha{1};
};
