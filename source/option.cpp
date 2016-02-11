//
// option.cpp for option in /home/pedous_c/rendu/cpp_bomberman
// 
// Made by pedous_c
// Login   <pedous_c@epitech.net>
// 
// Started on Fri Jun 12 09:39:56 2015 pedous_c
// Last update Sat Jun 13 13:50:47 2015 pedous_c
//

#include "option.hpp"
#include "scenemanager.h"
#include "asset.h"
#include "gameengine.h"
#include "game.h"
#include "camera.h"
#include "button.hpp"

extern "C"
void	onBack()
{
  CSceneManager::setActiveScene("menu");
}

COption::COption() : _enter(true), _count(1), _index(0), _save(0), _countUp(0), _countDown(0)
{
  this->initialize();
}

COption::~COption()
{

}

bool	COption::initialize()
{
  _cameraOption = new CCamera(glm::vec3(0, 0, 20), glm::vec3(0, 0, 0), 50);

  _resolution.push_back(glm::vec2(800, 600));
  _resolution.push_back(glm::vec2(1024, 600));
  _resolution.push_back(glm::vec2(1280, 960));
  _resolution.push_back(glm::vec2(1440, 900));
  _resolution.push_back(glm::vec2(1280, 1024));
  _resolution.push_back(glm::vec2(1600, 900));
  _resolution.push_back(glm::vec2(1680, 1050));
  _resolution.push_back(glm::vec2(1920, 1080));

  _choose.push_back(new CButton(glm::vec3(-6, 3, 0), glm::vec2(5, 2.5f), CAsset::getTexture("res1Pressed"), NULL));
  _choose.push_back(new CButton(glm::vec3(-3, 3, 0), glm::vec2(5, 2.5f), CAsset::getTexture("res2Idle"), NULL));
  _choose.push_back(new CButton(glm::vec3(0, 3, 0), glm::vec2(5, 2.5f), CAsset::getTexture("res3Idle"), NULL));
  _choose.push_back(new CButton(glm::vec3(3, 3, 0), glm::vec2(5, 2.5f), CAsset::getTexture("res4Idle"), NULL));
  _choose.push_back(new CButton(glm::vec3(-6, 1.5f, 0), glm::vec2(5, 2.5f), CAsset::getTexture("res5Idle"), NULL));
  _choose.push_back(new CButton(glm::vec3(-3, 1.5f, 0), glm::vec2(5, 2.5f), CAsset::getTexture("res6Idle"), NULL));
  _choose.push_back(new CButton(glm::vec3(0, 1.5f, 0), glm::vec2(5, 2.5f), CAsset::getTexture("res7Idle"), NULL));
  _choose.push_back(new CButton(glm::vec3(3, 1.5f, 0), glm::vec2(5, 2.5f), CAsset::getTexture("res8Idle"), NULL));
  _choose.push_back(new CButton(glm::vec3(-5, -4, 0), glm::vec2(5, 2.5f), CAsset::getTexture("backIdle"), onBack));

  _change.push_back(CAsset::getTexture("res1Pressed"));
  _change.push_back(CAsset::getTexture("res2Pressed"));
  _change.push_back(CAsset::getTexture("res3Pressed"));
  _change.push_back(CAsset::getTexture("res4Pressed"));
  _change.push_back(CAsset::getTexture("res5Pressed"));
  _change.push_back(CAsset::getTexture("res6Pressed"));
  _change.push_back(CAsset::getTexture("res7Pressed"));
  _change.push_back(CAsset::getTexture("res8Pressed"));
  _change.push_back(CAsset::getTexture("backPressed"));

  _change2.push_back(CAsset::getTexture("res1Idle"));
  _change2.push_back(CAsset::getTexture("res2Idle"));
  _change2.push_back(CAsset::getTexture("res3Idle"));
  _change2.push_back(CAsset::getTexture("res4Idle"));
  _change2.push_back(CAsset::getTexture("res5Idle"));
  _change2.push_back(CAsset::getTexture("res6Idle"));
  _change2.push_back(CAsset::getTexture("res7Idle"));
  _change2.push_back(CAsset::getTexture("res8Idle"));
  _change2.push_back(CAsset::getTexture("backIdle"));

  _background = new CButton(glm::vec3(-6.25f, -4.8f, 0), glm::vec2(25, 20), CAsset::getTexture("BackgroundOption"), NULL);

  return true;
}
#include <iostream>
bool	COption::update(__attribute__((unused))gdl::Clock const &clock, __attribute__((unused))const gdl::Input &input)
{
  if ((const_cast<gdl::Input&>(input)).getKey(SDLK_q) && _countUp == 1)
      this->OnUp();
  else if (!((const_cast<gdl::Input&>(input)).getKey(SDLK_q)))
    _countUp = 1;

  if ((const_cast<gdl::Input&>(input)).getKey(SDLK_d) && _countDown == 1)
    this->OnDown();
  else if (!((const_cast<gdl::Input&>(input)).getKey(SDLK_d)))
    _countDown = 1;

  if  ((const_cast<gdl::Input&>(input)).getKey(SDLK_RETURN) && _enter == false)
    {
      if (_count == 1 && _index == 8)
	{
	  CSceneManager::removeScene("Option");
	  CSceneManager::setActiveScene("menu");
	}
      else if (_count == 1 && _index >= 0 && _index <= 7)
	CGameEngine::resizeWindow(_resolution[_index]);
      ++_count;
    }
  else if (!((const_cast<gdl::Input&>(input)).getKey(SDLK_RETURN)))
    {
      _enter = false;
      _count = 1;
    }

 if (_index != _save)
    {
      _choose[_save]->setTexture(_change2[_save]);
      _choose[_index]->setTexture(_change[_index]);
      _save = _index;
    }
  return true;
}

void	COption::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
  shader.bind();
  shader.setUniform("view", _cameraOption->getTransformation());
  shader.setUniform("projection", _cameraOption->getProjection());

  for (int index = 0; index < (signed)_choose.size(); ++index)
    _choose[index]->draw(shader, clock);
  _background->draw(shader, clock);
}

void	COption::OnUp()
{
  ++_countUp;
  if ((_index - 1) < 0)
    _index = (signed)_choose.size() - 1;
  else
    --_index;
}

void	COption::OnDown()
{
  ++_countDown;
  if (_index + 1 > (signed)_choose.size() - 1)
    _index = 0;
  else
    ++_index;
}
