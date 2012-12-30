#pragma once
#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreConfigFile.h>

//Note might be needed for sdktray
#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

#include <SdkTrays.h>
#include <SdkCameraMan.h>

class Manager;

class Ogre_Manager : public Ogre::FrameListener,
                     public Ogre::WindowEventListener,
                     OgreBites::SdkTrayListener,
                     public OIS::KeyListener,
                     public OIS::MouseListener
{
public:
  Ogre_Manager(Manager *mgr);
  ~Ogre_Manager();
  void init();
  bool go();


  Manager * manager;
  Ogre::Root * root;
  Ogre::Camera * camera;

  Ogre::SceneManager * scene_mgr;
  Ogre::RenderWindow * window;
  Ogre::String resources_cfg;
  Ogre::String plugins_cfg;

  OgreBites::SdkTrayManager * tray_mgr;
  OgreBites::SdkCameraMan * camera_man;
  OgreBites::ParamsPanel * details_panel;

  bool cursor_was_visible;
  bool shutdown;

  // Ogre::FrameListener
  virtual bool frameRenderingQueued(const Ogre::FrameEvent & evt);

  // Ogre::WindowEventListener
  virtual void windowResized(Ogre::RenderWindow * rw);
  virtual void windowClosed(Ogre::RenderWindow * rw);


  /* OIS stuff */

  OIS::InputManager* input_manager;
  OIS::Mouse*    mouse;
  OIS::Keyboard* keyboard;

  // OIS::KeyListener
  virtual bool keyPressed( const OIS::KeyEvent &arg );
  virtual bool keyReleased( const OIS::KeyEvent &arg );
  // OIS::MouseListener
  virtual bool mouseMoved( const OIS::MouseEvent &arg );
  virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
  virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );

protected:
  void setup_framelistener();
};
