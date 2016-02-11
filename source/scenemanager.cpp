#include <iostream>
#include "scenemanager.h"
#include "gamescene.h"

IGameScene *CSceneManager::_activeScene = 0;
std::list<std::pair<IGameScene*, std::string> > CSceneManager::_scenes;

CSceneManager::CSceneManager()
{}

CSceneManager::~CSceneManager()
{}

bool CSceneManager::addScene(IGameScene *scene, std::string const& name, bool setactive)
{
   if (!scene)
   {
      std::cerr << "[Warning]: trying to add a null scene pointer." << std::endl;
      return false;
   }
   for (std::list<std::pair<IGameScene*, std::string> >::iterator it = _scenes.begin(); it != _scenes.end(); ++it)
   {
      if (name == (*it).second)
      {
         std::cerr << "[Error]: cannot add scene '" << name << "' is already used." << std::endl;
         return false;
      }
   }
   _scenes.push_front(std::pair<IGameScene*, std::string>(scene, name));
   if (setactive)
      _activeScene = scene;
   return true;
}

bool CSceneManager::removeScene(std::string const& name)
{
   for (std::list<std::pair<IGameScene*, std::string> >::iterator it = _scenes.begin(); it != _scenes.end(); ++it)
   {
      if (name == (*it).second)
      {
         if (_activeScene == (*it).first)
            _activeScene = 0;
         _scenes.erase(it);
         return true;
      }
   }
   std::cerr << "[Error]: unknown scene '" << name << "'." << std::endl;
   return false;
}

bool CSceneManager::setActiveScene(std::string const& name)
{
   for (std::list<std::pair<IGameScene*, std::string> >::iterator it = _scenes.begin(); it != _scenes.end(); ++it)
   {
      if (name == (*it).second)
      {
         _activeScene = (*it).first;
         return true;
      }
   }
   std::cerr << "[Error]: unknown scene '" << name << "'." << std::endl;
   return false;
}

IGameScene *CSceneManager::getActiveScene()
{
   return _activeScene;
}
