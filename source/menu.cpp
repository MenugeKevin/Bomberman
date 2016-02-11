//
// menu.cpp for menu in /home/pedous_c/rendu/cpp_bomberman
//
// Made by pedous_c
// Login   <pedous_c@epitech.net>
//
// Started on Wed Jun 10 12:21:52 2015 pedous_c
// Last update Sun Jun 14 21:58:10 2015 pedous_c
//

#include <iostream>
#include "menu.hpp"
#include "scenemanager.h"
#include "asset.h"
#include "gameengine.h"
#include "game.h"
#include "option.hpp"
#include "camera.h"

extern "C"
void	onStart()
{
  IGameScene       *game;

  if (CGameEngine::_nbAI == -1)
    game = new CGame(false, 7, CGameEngine::_mapSize);
  else
    game = new CGame(false, CGameEngine::_nbAI, CGameEngine::_mapSize);

  CSceneManager::addScene(game, "game", true);
}

extern "C"
void	onMulti()
{
  IGameScene       *game;

  if (CGameEngine::_nbAI == -1)
    game = new CGame(true, 6, CGameEngine::_mapSize);
  else
    game = new CGame(true, CGameEngine::_nbAI, CGameEngine::_mapSize);

  CSceneManager::addScene(game, "game", true);
}

extern "C"
void	onOption()
{
  IGameScene       *option = new COption();

  CSceneManager::addScene(option, "Option", true);
}

extern "C"
void	onQuit()
{
  CGameEngine::_quitApplication = true;
}

CMenu::CMenu() :  _count(0), _index(0), _countUp(0), _countDown(0)
{
  this->initialize();
}

CMenu::~CMenu()
{
  CSceneManager::removeScene("menu");
  for (int index = 0; index < (signed)_choose.size(); ++index)
    delete (_choose[index]);
  for (int index = 0; index < (signed)_tools.size(); ++index)
    delete (_tools[index]);
}

bool	CMenu::initialize()
{
  _cameraMenu = new CCamera(glm::vec3(0, 0, 20), glm::vec3(0, 0, 0), 50);

  _moveCursor[0] = glm::vec3(-2.5f, 3, 0);
  _moveCursor[1] = glm::vec3(-1, 1, 0);
  _moveCursor[2] = glm::vec3(-5, -1, 0);
  _moveCursor[3] = glm::vec3(-7, -3, 0);

  _choose.push_back(new CButton(glm::vec3(-6.95f, 3, 0), glm::vec2(10, 2.5f), CAsset::getTexture("Solo"), onStart));
  _choose.push_back(new CButton(glm::vec3(-6.5f, 2, 0), glm::vec2(10, 2.5f), CAsset::getTexture("Multi"), onMulti));
  _choose.push_back(new CButton(glm::vec3(-7.55f, 1, 0), glm::vec2(10, 2.5f), CAsset::getTexture("Option"), onOption));
  _choose.push_back(new CButton(glm::vec3(-7.95f, 0, 0), glm::vec2(10, 2.5f), CAsset::getTexture("Quit"), onQuit));

  _tools.push_back(new CButton(glm::vec3(-2, 3, 0), glm::vec2(2.5f, 2.5f), CAsset::getTexture("Cursor"), NULL));
  _tools.push_back(new CButton(glm::vec3(1, 3, 0), glm::vec2(10, 2.5f), CAsset::getTexture("Title"), NULL));
  _tools.push_back(new CButton(glm::vec3(-9.5f, -4.8f, 0), glm::vec2(40, 25), CAsset::getTexture("Background"), NULL));

  return true;
}

bool	CMenu::update(__attribute__((unused))gdl::Clock const &clock, __attribute__((unused))const gdl::Input &input)
{
  if ((const_cast<gdl::Input&>(input)).getKey(SDLK_z) && _countUp == 1)
      this->OnUp();
  else if (!((const_cast<gdl::Input&>(input)).getKey(SDLK_z)))
    _countUp = 1;

  if ((const_cast<gdl::Input&>(input)).getKey(SDLK_s) && _countDown == 1)
    this->OnDown();
  else if (!((const_cast<gdl::Input&>(input)).getKey(SDLK_s)))
    _countDown = 1;


  if (((const_cast<gdl::Input&>(input)).getKey(SDLK_RETURN)) && _index == 1)
    {
      if (_count == 1)
	{
	  _choose[_index]->OnClick();
	  return false;
	}
      ++_count;
    }
  else if ((const_cast<gdl::Input&>(input)).getKey(SDLK_RETURN))
    {
      if (_count == 1)
	  _choose[_index]->OnClick();
      ++_count;
    }
  else
    _count = 1;

  _tools[0]->setPosition(_moveCursor[_index]);

  for (int index = 0; index < (signed)_choose.size(); ++index)
    _choose[index]->update(clock, input);
  return true;
}

void	CMenu::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
  shader.bind();
  shader.setUniform("view", _cameraMenu->getTransformation());
  shader.setUniform("projection", _cameraMenu->getProjection());
  _tools[0]->draw(shader, clock);
  for (int index = 0; index < (signed)_choose.size(); ++index)
    _choose[index]->draw(shader, clock);
  for (int index = 1; index < (signed)_tools.size(); ++index)
    _tools[index]->draw(shader, clock);
}

void	CMenu::OnUp()
{
  ++_countUp;
  if ((_index - 1) < 0)
    _index = (signed)_choose.size() - 1;
  else
    --_index;
}

void	CMenu::OnDown()
{
  ++_countDown;
  if (_index + 1 > (signed)_choose.size() - 1)
    _index = 0;
  else
    ++_index;
}
