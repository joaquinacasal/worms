#ifndef __IDRAWABLE__
#define __IDRAWABLE__

class ConsoleDrawer;

/* Interfaz que representa a los objetos dibujables.
 */
class IDrawable {

public:
  virtual void be_drawn_by_console(ConsoleDrawer* console_drawer) = 0;
};


#endif //__IDRAWABLE__
