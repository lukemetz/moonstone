#include "Ogre_Manager.hpp"
#include "Manager.hpp"

Ogre_Manager::Ogre_Manager(Manager * mgr) : root(0),
                               camera(0),
                               scene_mgr(0),
                               window(0),
                               resources_cfg(Ogre::StringUtil::BLANK),
                               plugins_cfg(Ogre::StringUtil::BLANK),
                               tray_mgr(0),
                               camera_man(0),
                               details_panel(0),
                               cursor_was_visible(false),
                               shutdown(false),
                               input_manager(0),
                               mouse(0),
                               keyboard(0),
                               manager(mgr)
{
}

Ogre_Manager::~Ogre_Manager()
{
  if (tray_mgr)
    delete tray_mgr;
  if (camera_man)
    delete camera_man;

  Ogre::WindowEventUtilities::removeWindowEventListener(window, this);
  //trigger callback
  windowClosed(window);
  delete root;
}


bool Ogre_Manager::go()
{
  resources_cfg = "resources.cfg";
  plugins_cfg = "plugins.cfg";

  root = new Ogre::Root(plugins_cfg);

  //Set up resources

  Ogre::ConfigFile cf;
  cf.load(resources_cfg);
  Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();

  Ogre::String sec_name, type_name, arch_name;

  while(seci.hasMoreElements()) {
    sec_name = seci.peekNextKey();
    Ogre::ConfigFile::SettingsMultiMap * settings = seci.getNext();
    Ogre::ConfigFile::SettingsMultiMap::iterator i;
    for (i = settings->begin(); i != settings->end(); ++i) {
      type_name = i->first;
      arch_name = i->second;
      Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
          arch_name, type_name, sec_name);
    }
  }

  //Configure
  //RestoreConfig gets config from ogre.cfg
  if (root->restoreConfig() || root->showConfigDialog()) {
    window = root->initialise(true, "moonstone_demo");
  } else {
    return false;
  }

  scene_mgr = root->createSceneManager(Ogre::ST_GENERIC);

  camera = scene_mgr->createCamera("Default_Cam");
  camera->setPosition(Ogre::Vector3(0,0,80));
  camera->lookAt(Ogre::Vector3(0,0,-300));
  camera->setNearClipDistance(5);

  camera_man = new OgreBites::SdkCameraMan(camera);
  Ogre::Viewport * vp = window->addViewport(camera);
  vp->setBackgroundColour(Ogre::ColourValue(0,0,0));

  camera->setAspectRatio(
      Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));

  Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);

  Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

  Ogre::Entity * ogreHead = scene_mgr->createEntity("Head", "ogrehead.mesh");

  Ogre::SceneNode * headNode = scene_mgr->getRootSceneNode()->createChildSceneNode();
  headNode->attachObject(ogreHead);

  scene_mgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
  Ogre::Light * l = scene_mgr->createLight("Main_Light");
  l->setPosition(20, 80, 50);

  /*
   * Started cfut and paste"
   */

  Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");
  OIS::ParamList pl;
  size_t windowHnd = 0;
  std::ostringstream windowHndStr;

  window->getCustomAttribute("WINDOW", &windowHnd);
  windowHndStr << windowHnd;
  pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

  input_manager = OIS::InputManager::createInputSystem( pl );

  keyboard = static_cast<OIS::Keyboard*>(input_manager->createInputObject( OIS::OISKeyboard, true ));
  mouse = static_cast<OIS::Mouse*>(input_manager->createInputObject( OIS::OISMouse, true ));

  mouse->setEventCallback(this);
  keyboard->setEventCallback(this);

  //Set initial mouse clipping size
  windowResized(window);

  //Register as a Window listener
  Ogre::WindowEventUtilities::addWindowEventListener(window, this);

  tray_mgr = new OgreBites::SdkTrayManager("InterfaceName", window, mouse, this);
  tray_mgr->showFrameStats(OgreBites::TL_BOTTOMLEFT);
  tray_mgr->showLogo(OgreBites::TL_BOTTOMRIGHT);
  tray_mgr->hideCursor();

  // create a params panel for displaying sample details
  Ogre::StringVector items;
  items.push_back("cam.pX");
  items.push_back("cam.pY");
  items.push_back("cam.pZ");
  items.push_back("");
  items.push_back("cam.oW");
  items.push_back("cam.oX");
  items.push_back("cam.oY");
  items.push_back("cam.oZ");
  items.push_back("");
  items.push_back("Filtering");
  items.push_back("Poly Mode");

  details_panel= tray_mgr->createParamsPanel(OgreBites::TL_NONE, "DetailsPanel", 200, items);
  details_panel->setParamValue(9, "Bilinear");
  details_panel->setParamValue(10, "Solid");
  details_panel->hide();

  root->addFrameListener(this);
//-------------------------------------------------------------------------------------
  root->startRendering();

  return true;
}

bool Ogre_Manager::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
  if(window->isClosed())
      return false;

  if(shutdown)
      return false;

  //Need to capture/update each device
  keyboard->capture();
  mouse->capture();

  tray_mgr->frameRenderingQueued(evt);

  if (!tray_mgr->isDialogVisible())
  {
      camera_man->frameRenderingQueued(evt);   // if dialog isn't up, then update the camera
      if (details_panel->isVisible())   // if details panel is visible, then update its contents
      {
          details_panel->setParamValue(0, Ogre::StringConverter::toString(camera->getDerivedPosition().x));
          details_panel->setParamValue(1, Ogre::StringConverter::toString(camera->getDerivedPosition().y));
          details_panel->setParamValue(2, Ogre::StringConverter::toString(camera->getDerivedPosition().z));
          details_panel->setParamValue(4, Ogre::StringConverter::toString(camera->getDerivedOrientation().w));
          details_panel->setParamValue(5, Ogre::StringConverter::toString(camera->getDerivedOrientation().x));
          details_panel->setParamValue(6, Ogre::StringConverter::toString(camera->getDerivedOrientation().y));
          details_panel->setParamValue(7, Ogre::StringConverter::toString(camera->getDerivedOrientation().z));
      }
  }
  //Update the manager
  manager->update(evt.timeSinceLastFrame);
  return true;
}
//-------------------------------------------------------------------------------------
bool Ogre_Manager::keyPressed( const OIS::KeyEvent &arg )
{
  if (tray_mgr->isDialogVisible()) return true;   // don't process any more keys if dialog is up

  if (arg.key == OIS::KC_F)   // toggle visibility of advanced frame stats
  {
      tray_mgr->toggleAdvancedFrameStats();
  }
  else if (arg.key == OIS::KC_G)   // toggle visibility of even rarer debugging details
  {
      if (details_panel->getTrayLocation() == OgreBites::TL_NONE)
      {
          tray_mgr->moveWidgetToTray(details_panel, OgreBites::TL_TOPRIGHT, 0);
          details_panel->show();
      }
      else
      {
          tray_mgr->removeWidgetFromTray(details_panel);
          details_panel->hide();
      }
  }
  else if (arg.key == OIS::KC_T)   // cycle texture filtering mode
  {
      Ogre::String newVal;
      Ogre::TextureFilterOptions tfo;
      unsigned int aniso;

      switch (details_panel->getParamValue(9).asUTF8()[0])
      {
      case 'B':
          newVal = "Trilinear";
          tfo = Ogre::TFO_TRILINEAR;
          aniso = 1;
          break;
      case 'T':
          newVal = "Anisotropic";
          tfo = Ogre::TFO_ANISOTROPIC;
          aniso = 8;
          break;
      case 'A':
          newVal = "None";
          tfo = Ogre::TFO_NONE;
          aniso = 1;
          break;
      default:
          newVal = "Bilinear";
          tfo = Ogre::TFO_BILINEAR;
          aniso = 1;
      }

      Ogre::MaterialManager::getSingleton().setDefaultTextureFiltering(tfo);
      Ogre::MaterialManager::getSingleton().setDefaultAnisotropy(aniso);
      details_panel->setParamValue(9, newVal);
  }
  else if (arg.key == OIS::KC_R)   // cycle polygon rendering mode
  {
      Ogre::String newVal;
      Ogre::PolygonMode pm;

      switch (camera->getPolygonMode())
      {
      case Ogre::PM_SOLID:
          newVal = "Wireframe";
          pm = Ogre::PM_WIREFRAME;
          break;
      case Ogre::PM_WIREFRAME:
          newVal = "Points";
          pm = Ogre::PM_POINTS;
          break;
      default:
          newVal = "Solid";
          pm = Ogre::PM_SOLID;
      }

      camera->setPolygonMode(pm);
      details_panel->setParamValue(10, newVal);
  }
  else if(arg.key == OIS::KC_F5)   // refresh all textures
  {
      Ogre::TextureManager::getSingleton().reloadAll();
  }
  else if (arg.key == OIS::KC_SYSRQ)   // take a screenshot
  {
      window->writeContentsToTimestampedFile("screenshot", ".jpg");
  }
  else if (arg.key == OIS::KC_ESCAPE)
  {
      shutdown = true;
  }

  camera_man->injectKeyDown(arg);
  return true;
}

bool Ogre_Manager::keyReleased( const OIS::KeyEvent &arg )
{
  camera_man->injectKeyUp(arg);
  return true;
}

bool Ogre_Manager::mouseMoved( const OIS::MouseEvent &arg )
{
  if (tray_mgr->injectMouseMove(arg)) return true;
  camera_man->injectMouseMove(arg);
  return true;
}

bool Ogre_Manager::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
  if (tray_mgr->injectMouseDown(arg, id)) return true;
  camera_man->injectMouseDown(arg, id);
  return true;
}

bool Ogre_Manager::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
  if (tray_mgr->injectMouseUp(arg, id)) return true;
  camera_man->injectMouseUp(arg, id);
  return true;
}

//Adjust mouse clipping area
void Ogre_Manager::windowResized(Ogre::RenderWindow* rw)
{
  unsigned int width, height, depth;
  int left, top;
  rw->getMetrics(width, height, depth, left, top);

  const OIS::MouseState &ms = mouse->getMouseState();
  ms.width = width;
  ms.height = height;
}

//Unattach OIS before window shutdown (very important under Linux)
void Ogre_Manager::windowClosed(Ogre::RenderWindow* rw)
{
  //Only close for window that created OIS (the main window in these demos)
  if( rw == window )
  {
      if( input_manager )
      {
          input_manager->destroyInputObject( mouse );
          input_manager->destroyInputObject( keyboard );

          OIS::InputManager::destroyInputSystem(input_manager);
          input_manager = 0;
      }
  }
}



