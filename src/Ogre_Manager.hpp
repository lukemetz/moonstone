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
//^^Check

#include <SdkTrays.h>
#include <SdkCameraMan.h>

#include "DeferredShading.h"


class Manager;
class Ogre_Manager;
class OIS_Input_Manager;

class Ogre_Manager : public Ogre::FrameListener,
                     public Ogre::WindowEventListener,
                     OgreBites::SdkTrayListener
{
public:
  Ogre_Manager(Manager *mgr);
  ~Ogre_Manager();
  void init();
  void set_ois_input_manager(OIS_Input_Manager * ois_input_manager);
  bool go();


  Manager * manager;
  OIS_Input_Manager * input_manager;
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

  bool keyPressed( const OIS::KeyEvent &arg );
  bool keyReleased( const OIS::KeyEvent &arg );
  bool mouseMoved( const OIS::MouseEvent &arg );
  bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
  bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );

  static Ogre_Manager* get_instance();
  static Ogre_Manager* instance;

  DeferredShadingSystem * deferred_shading_system;
protected:
  void setup_framelistener();
};
