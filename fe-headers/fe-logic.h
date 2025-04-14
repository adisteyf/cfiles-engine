#ifndef FE_LOGIC
#define FE_LOGIC

#include <stdlib.h>

extern "C" {
  void   zigGreetings ();
  void   addModel (void * modelptr);
  void * getModel (size_t index);
}

#endif // FE_LOGIC
