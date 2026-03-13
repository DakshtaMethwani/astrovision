#ifndef ZODIAC_H
#define ZODIAC_H

#include <string>

using namespace std;

class Zodiac {
private:
  std::string name;
  std::string element;
  std::string rulingPlanet;
  std::string traits;

public:
  // ✅ Default constructor (needed for std::map)
  Zodiac() {}

  // ✅ Parameterized constructor
  Zodiac(std::string n, std::string e, std::string r, std::string t) {
    name = n;
    element = e;
    rulingPlanet = r;
    traits = t;
  }

  // ✅ Getter functions
  std::string getName() const { return name; }

  std::string getElement() const { return element; }

  std::string getRulingPlanet() const { return rulingPlanet; }

  std::string getTraits() const { return traits; }
};

#endif