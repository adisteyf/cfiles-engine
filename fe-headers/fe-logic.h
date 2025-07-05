#ifndef FE_LOGIC
#define FE_LOGIC

#include "model.h"
#include <stdlib.h>

extern "C" {
  void    zigGreetings ();
  void    addModel (Model * modelptr);
  Model * getModel (size_t index);
  void    deleteModels ();
  size_t  getModelsLen ();
  void    drawModels         (void * shptr);
	void    drawModelsOneColor (void * shptr, float dcolor[4]);
  void    drawModel          (size_t index, void * shptr);
}

#endif // FE_LOGIC
