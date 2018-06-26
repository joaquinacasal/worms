#ifndef __IDRAWABLE__
#define __IDRAWABLE__

class ConsoleDrawer;
class SdlWindow;

/* Interfaz que representa a los objetos dibujables.
 */
class IDrawable {
public:
  virtual void be_drawn_by_console(ConsoleDrawer* console_drawer) = 0;
  virtual void be_drawn(SdlWindow* window) = 0;
  virtual ~IDrawable(){};
};


#endif //__IDRAWABLE__
