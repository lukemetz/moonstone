#include "OIS_Input_Manager.hpp"
#include "Ogre_Manager.hpp"

OIS_Input_Manager * OIS_Input_Manager::instance = nullptr;

OIS_Input_Manager::OIS_Input_Manager()
{
  instance = this;
}

bool OIS_Input_Manager::keyPressed( const OIS::KeyEvent &arg )
{
  ogre_manager->keyPressed(arg);
  return true;
}

bool OIS_Input_Manager::keyReleased( const OIS::KeyEvent &arg )
{
  ogre_manager->keyReleased(arg);
  return true;
}

bool OIS_Input_Manager::mouseMoved( const OIS::MouseEvent &arg )
{
  ogre_manager->mouseMoved(arg);
  return true;
}

bool OIS_Input_Manager::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
  ogre_manager->mousePressed(arg, id);
  return true;
}

bool OIS_Input_Manager::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
  ogre_manager->mouseReleased(arg, id);
  return true;
}

void OIS_Input_Manager::destroy_input_manager()
{
}

void OIS_Input_Manager::update_clipping_area(unsigned int width, unsigned int height)
{
  const OIS::MouseState &ms = mouse->getMouseState();
  ms.width = width;
  ms.height = height;
}

void OIS_Input_Manager::bind_to_window(std::string name)
{
  OIS::ParamList pl;
  pl.insert(std::make_pair(std::string("WINDOW"), name));

#if defined OIS_LINUX_PLATFORM
  pl.insert(std::make_pair(std::string("x11_mouse_grab"), std::string("false")));
  pl.insert(std::make_pair(std::string("x11_mouse_hide"), std::string("false")));
  pl.insert(std::make_pair(std::string("x11_keyboard_grab"), std::string("false")));
  pl.insert(std::make_pair(std::string("XAutoRepeatOn"), std::string("true")));
#endif
  input_manager = OIS::InputManager::createInputSystem( pl );

  keyboard = static_cast<OIS::Keyboard*>(input_manager->createInputObject( OIS::OISKeyboard, true ));
  mouse = static_cast<OIS::Mouse*>(input_manager->createInputObject( OIS::OISMouse, true ));

  mouse->setEventCallback(this);
  keyboard->setEventCallback(this);
}

void OIS_Input_Manager::capture()
{
  keyboard->capture();
  mouse->capture();
}

void OIS_Input_Manager::populate_inputs(bool * keys,
                                        bool * mouse_buttons,
                                        int * mouse_dx, int * mouse_dy,
                                        int * mouse_x, int * mouse_y)
{
  for(int i=0; i < 222; i++) {
    keys[i] = keyboard->isKeyDown((OIS::KeyCode)i);
  }
  const OIS::MouseState & ms = mouse->getMouseState();
  for(int i=0; i < 8; i++) {
    mouse_buttons[i] = ms.buttonDown((OIS::MouseButtonID)i);
  }

  *mouse_x = ms.X.abs;
  *mouse_y = ms.Y.abs;

  *mouse_dx = ms.X.rel;
  *mouse_dy = ms.Y.rel;
}

OIS_Input_Manager * OIS_Input_Manager::get_instance()
{
  return instance;
}
