#include "vector"
#include "../src/ObjectID.C"
#ifdef __CINT__ 
#pragma link C++ nestedclasses;
#pragma link C++ nestedtypedefs;
#pragma link C++ class vector<Electron*>+;
#pragma link C++ class vector<Electron*>::*;
#ifdef G__VECTOR_HAS_CLASS_ITERATOR
#pragma link C++ operators vector<Electron*>::iterator;
#pragma link C++ operators vector<Electron*>::const_iterator;
#pragma link C++ operators vector<Electron*>::reverse_iterator;
#endif
#endif
