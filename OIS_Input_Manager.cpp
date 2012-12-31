#include "OIS_Input_Manager.hpp"
#include "Ogre_Manager.hpp"

OIS_Input_Manager::OIS_Input_Manager()
{
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
