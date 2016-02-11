#include <algorithm>
#include "map.h"
#include "game.h"
#include "player.h"
#include "camera.h"
#include "gameengine.h"
#include "scenemanager.h"

CMap *CGame::_level = 0;
std::list<AEntity*> CGame::_entities;

CGame::CGame(bool multiplayer, int botNum, glm::vec2 const& mapSize) :
   _ready(false)
{
   _players[0] = new CPlayer(CPlayer::PLAYER1);
   _players[0]->translate(glm::vec3(25, 25, 0));
   _players[0]->rotate(glm::vec3(1, 0, 0), 90);
   _players[0]->scale(glm::vec3(0.0025f, 0.0025f, 0.0025f));
   _camera = new CCamera(glm::vec3(0, 30, 20), glm::vec3(0, 0, 0), 30);
   _camera->setParent(_players[0]);
   _playerslist.push_front(_players[0]);
   _entities.push_back(_camera);
   if (multiplayer)
   {
      _players[1] = new CPlayer(CPlayer::PLAYER2);
      _players[1]->scale(glm::vec3(0.0025f, 0.0025f, 0.0025f));
      _players[1]->rotate(glm::vec3(1, 0, 0), 90);
      _playerslist.push_front(_players[1]);
      delete _camera;
      _camera = new CCamera(glm::vec3((mapSize.x / 2)* TILESIZE, (mapSize.y / 2), std::max(mapSize.x, mapSize.y) * 2), glm::vec3((mapSize.x / 2)* TILESIZE, (mapSize.y / 2) * TILESIZE, 0), 30);
   }
   for (int i = 0; i < botNum; ++i)
   {
      CPlayer *bot = new CPlayer(static_cast<CPlayer::EControlType>(-1));
      bot->rotate(glm::vec3(1, 0, 0), 90);
      bot->scale(glm::vec3(0.0025f, 0.0025f, 0.0025f));
      _playerslist.push_front(bot);
   }
   _level = new CMap(_playerslist.size(), mapSize.x, mapSize.y);
   spawnPlayers();
   _ready = true;
}

CGame::~CGame()
{
   if (_level)
      delete _level;
   for (std::list<CPlayer*>::iterator it = _playerslist.begin(); it != _playerslist.end(); ++it)
      delete *it;
   for (std::list<AEntity*>::iterator it = _entities.begin(); it != _entities.end(); ++it)
      delete *it;
}

CMap *CGame::getLevel()
{
   return _level;
}

void CGame::win()
{
   CSceneManager::setActiveScene("menu");
   CSceneManager::removeScene("game");
}

void CGame::spawnPlayers()
{
   std::list<CPlayer*>::iterator it = _playerslist.begin();

   for (int j = 0; j < _level->size(); ++j)
   {
      for (unsigned i = 0; i < (*_level)[j].size(); ++i)
      {
         if ((*_level)[j][i]->getType() == CMap::ATile::PLAYER)
         {
            (*_level)[j][i]->setType(CMap::ATile::EMPTY);
            (*it)->setPosition(glm::vec3(i + (TILESIZE / 2.f), j + (TILESIZE / 2.f), 0));
            (*_level)[j][i]->addEntity(*it);
            if (++it == _playerslist.end())
               return;
         }
      }
   }
   return;
}

void CGame::draw(gdl::AShader& shader, gdl::Clock const& clock)
{
   shader.bind();
   shader.setUniform("view", _camera->getTransformation());
   shader.setUniform("projection", _camera->getProjection());
   if (_level)
      _level->draw(shader);
   for (std::list<CPlayer*>::iterator it = _playerslist.begin(); it != _playerslist.end(); ++it)
      (*it)->draw(shader, clock);
   for (std::list<AEntity*>::iterator it = _entities.begin(); it != _entities.end(); ++it)
      (*it)->draw(shader, clock);
   return;
}

bool CGame::update(gdl::Clock const& clock, gdl::Input const& input)
{
   int alive = 0;
   for (std::list<CPlayer*>::iterator it = _playerslist.begin(); it != _playerslist.end(); ++it)
   {
      if ((*it)->isAlive())
      {
         ++alive;
         (*it)->update(clock, input, *_level);
      }
   }
   if (alive == 1)
      win();
   for (std::list<AEntity*>::iterator it = _entities.begin(); it != _entities.end(); ++it)
   {
      if ((*it)->isDeletable())
      {
         (*_level)[(*it)->getPosition().y][(*it)->getPosition().x]->removeEntity(*it);
         delete *it;
         _entities.erase(it);
         --it;
      }
      else
         (*it)->update(clock, input, *_level);
   }
   return true;
}
