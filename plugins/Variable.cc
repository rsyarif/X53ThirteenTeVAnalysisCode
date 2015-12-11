#include <iostream>
#include <string>

class Variable {

public:
  Variable(std::string n, int nb, float xmi, float xma,std::string Xax,std::string Yax);
  ~Variable();

  std::string name;
  int nbins;
  float xmin;
  float xmax;
  std::string Xaxis;
  std::string Yaxis;

};

Variable::~Variable(){};

Variable::Variable(std::string n, int nb, float xmi, float xma,std::string Xax, std::string Yax):
  name(n),nbins(nb),xmin(xmi),xmax(xma),Xaxis(Xax),Yaxis(Yax)
{

};
