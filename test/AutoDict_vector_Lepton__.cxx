#include "vector"
#include "../src/ObjectID.C"
#ifdef __CINT__ 
#pragma link C++ nestedclasses;
#pragma link C++ nestedtypedefs;
#pragma link C++ class vector<Lepton*>+;
#pragma link C++ class vector<Lepton*>::*;
#ifdef G__VECTOR_HAS_CLASS_ITERATOR
#pragma link C++ operators vector<Lepton*>::iterator;
#pragma link C++ operators vector<Lepton*>::const_iterator;
#pragma link C++ operators vector<Lepton*>::reverse_iterator;
#endif
#endif
