#include "camera.h"
#include "asset.h"
#include "gameengine.h"
#include "BreakableWall.hpp"
#include "gamescene.h"
#include "game.h"
#include "menu.hpp"

float             CGameEngine::_volume = 1.f;
float             CGameEngine::_musicVolume = 1.f;
glm::vec2         CGameEngine::_windowSize;
gdl::SdlContext   CGameEngine::_context;
gdl::BasicShader  CGameEngine::_shader;
bool		  CGameEngine::_quitApplication = false;
int		  CGameEngine::_nbAI = -1;
glm::vec2	  CGameEngine::_mapSize = glm::vec2(25, 25);

CGameEngine::CGameEngine()
{}

CGameEngine::~CGameEngine()
{}
#include <iostream>
bool CGameEngine::init()
{
  _quitApplication = false;
   _windowSize = glm::vec2(800, 600);
   if (!_context.start(800, 600, "My bomberman!"))
      return false;
   glEnable(GL_DEPTH_TEST);
   if (!_shader.load("./LibBomberman_linux_x64/shaders/basic.fp", GL_FRAGMENT_SHADER) || !_shader.load("./LibBomberman_linux_x64/shaders/basic.vp", GL_VERTEX_SHADER) || !_shader.build())
      return false;
return true;
}

float CGameEngine::getMusicVolume()
{
   return _musicVolume;
}

float CGameEngine::getMasterVolume()
{
   return _volume;
}

void CGameEngine::setMusicVolume(float const& volume)
{
   _musicVolume = volume;
   return;
}

void CGameEngine::setMasterVolume(float const& volume)
{
   _volume = volume;
   return;
}

glm::vec2 const& CGameEngine::getWindowSize()
{
   return _windowSize;
}

void CGameEngine::resizeWindow(glm::vec2 const& size)
{
  _windowSize = size;
  _context.stop();
  if (!_context.start(size.x, size.y, "My bomberman!"))
    throw;
  return;
}

void CGameEngine::loop()
{
   IGameScene		*menu = new CMenu();

   gdl::Clock		clock;
   gdl::Input		input;
   CSceneManager::addScene(menu, "menu", true);

   for (;!_quitApplication;)
   {
     _context.updateClock(clock);
      _context.updateInputs(input);
      if (input.getKey(SDLK_ESCAPE) || input.getInput(SDL_QUIT))
	break;
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      if (_activeScene)
	{
	  if (_activeScene->update(clock, input))
	    _activeScene->draw(_shader, clock);
	}
      _context.flush();
   }
   _context.stop();
   return;
}
