#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>
class Ogre_Manager;
class OIS_Input_Manager;

class OIS_Input_Manager : public OIS::KeyListener, public OIS::MouseListener
{
public:
  OIS_Input_Manager();
  OIS::InputManager* input_manager = nullptr;
  OIS::Mouse*    mouse = nullptr;
  OIS::Keyboard* keyboard = nullptr;
  Ogre_Manager * ogre_manager = nullptr;
  // OIS::KeyListener
  virtual bool keyPressed( const OIS::KeyEvent &arg );
  virtual bool keyReleased( const OIS::KeyEvent &arg );
  // OIS::MouseListener
  virtual bool mouseMoved( const OIS::MouseEvent &arg );
  virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
  virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );

  void destroy_input_manager();
  void update_clipping_area(unsigned int width, unsigned int height);
  void bind_to_window(std::string name);

  void capture();

  void populate_inputs(bool * keys,
                       bool * mouse,
                       int * mouse_dx, int * mouse_dy,
                       int * mouse_x, int * mouse_y);

  static OIS_Input_Manager * get_instance();
  static OIS_Input_Manager * instance;
};
