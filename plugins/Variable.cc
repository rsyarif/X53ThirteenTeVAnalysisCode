#include <iostream>
#include <string>

class Variable {

public:
  Variable(std::string n, int nb, float xmi, float xma);
  ~Variable();

  std::string name;
  int nbins;
  float xmin;
  float xmax;


};

Variable::~Variable(){};

Variable::Variable(std::string n, int nb, float xmi, float xma):
  name(n),nbins(nb),xmin(xmi),xmax(xma)
{
};
