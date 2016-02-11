#include "map.h"
#include "game.h"
#include "asset.h"
#include "player.h"
#include "explosive.h"

CPlayer::CPlayer(EControlType type) :
  AEntity(PLAYER),
  _explosivePower(3),
  _explosiveMaxNum(1),
  _explosiveOnGround(0),
  _movespeed(3.f),
  _speedmultiplier(1.f),
  _controlType(type)
{
   initialize();
}

CPlayer::~CPlayer()
{}

bool	CPlayer::initialize()
{
  if (_controlType == PLAYER1)
    {
      _key.push_back(SDLK_z);
      _key.push_back(SDLK_q);
      _key.push_back(SDLK_s);
      _key.push_back(SDLK_d);
      _key.push_back(SDLK_SPACE);
    }
  else if (_controlType == PLAYER2)
    {
      _key.push_back(SDLK_UP);
      _key.push_back(SDLK_LEFT);
      _key.push_back(SDLK_DOWN);
      _key.push_back(SDLK_RIGHT);
      _key.push_back(SDLK_RCTRL);
    }
  _point.push_back(&CPlayer::moveUp);
  _point.push_back(&CPlayer::moveLeft);
  _point.push_back(&CPlayer::moveDown);
  _point.push_back(&CPlayer::moveRight);
  _point.push_back(&CPlayer::placeExplosive);
  _model = CAsset::getModel("Player");
  return (true);
}

void CPlayer::hitByExplosion(AEntity const* trigger __attribute__((unused)))
{
   _alive = false;
   return;
}

void CPlayer::decrementExplosiveNumber()
{
   _explosiveOnGround -= 1;
   return;
}

bool CPlayer::update(gdl::Clock const& clock, gdl::Input const& input, CMap& level)
{
   if (!_alive)
      return false;
  float frametime = static_cast<float>(clock.getElapsed());

  for (unsigned i = 0; i < _key.size(); ++i)
    {
      if (((const_cast<gdl::Input&>(input)).getKey(_key[i], true)))
	  (this->*_point[i])(frametime, level);
    }
   return true;
}

void	CPlayer::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
   if (_alive)
      _model->draw(shader, getTransformation(), clock.getElapsed());
  return;
}

void	CPlayer::moveUp(float const& frametime, CMap& level)
{
   int x = (_position.x / TILESIZE), y = (_position.y / TILESIZE);
   float movespeed = (_movespeed * frametime) * _speedmultiplier;

   setAngle(glm::vec3(_rotation.x, 180, _rotation.z));
   level[y][x]->removeEntity(this);
   translate(glm::vec3(0.f, movespeed, 0.f));
   y = _position.y / TILESIZE;
   if (y >= level.size() - 1)
      y = level.size() - 1;
   if ((level[y][x]->getType() != CMap::ATile::PLAYER && level[y][x]->getType() != CMap::ATile::EMPTY) || !level[y][x]->canPassThrough(this))
   {
      _position.y += (y * TILESIZE) - _position.y - 0.1;
      y = _position.y / TILESIZE;
   }
   level[y][x]->addEntity(this);
   level[y][x]->getPowerups(this);
   return;
}

void	CPlayer::moveLeft(float const& frametime, CMap& level)
{
   int x = _position.x / TILESIZE, y = _position.y / TILESIZE;
   float movespeed = _movespeed * frametime * _speedmultiplier;

   setAngle(glm::vec3(_rotation.x, -90, _rotation.z));
   level[y][x]->removeEntity(this);
   translate(glm::vec3(-movespeed, 0.f, 0.f));
   x = (_position.x / TILESIZE);
   if (x < 0)
      x = 0;
   if ((level[y][x]->getType() != CMap::ATile::PLAYER && level[y][x]->getType() != CMap::ATile::EMPTY) || !level[y][x]->canPassThrough(this))
   {
      _position.x += ((x + 1) * TILESIZE) - _position.x;
      x = _position.x / TILESIZE;
   }
   level[y][x]->addEntity(this);
   level[y][x]->getPowerups(this);
   return;
}

void	CPlayer::moveDown(float const& frametime, CMap& level)
{
   int x = _position.x / TILESIZE, y = _position.y / TILESIZE;
   float movespeed = _movespeed * frametime * _speedmultiplier;

   setAngle(glm::vec3(_rotation.x, 0, _rotation.z));
   level[y][x]->removeEntity(this);
   translate(glm::vec3(0.f, -movespeed, 0.f));
   y = _position.y / TILESIZE;
   if (y < 0)
      y = 0;
   if ((level[y][x]->getType() != CMap::ATile::PLAYER && level[y][x]->getType() != CMap::ATile::EMPTY) || !level[y][x]->canPassThrough(this))
   {
      _position.y += ((y + 1) * TILESIZE) - _position.y;
      y = _position.y / TILESIZE;
   }
   level[y][x]->addEntity(this);
   level[y][x]->getPowerups(this);
   return;
}

void	CPlayer::moveRight(float const& frametime, CMap& level)
{
   int x = _position.x / TILESIZE, y = _position.y / TILESIZE;
   float movespeed = _movespeed * frametime * _speedmultiplier;

   setAngle(glm::vec3(_rotation.x, 90, _rotation.z));
   level[y][x]->removeEntity(this);
   translate(glm::vec3(movespeed, 0.f, 0.f));
   x = _position.x / TILESIZE;
   if (x >= (signed)level[y].size())
      x = level[y].size();
   if ((level[y][x]->getType() != CMap::ATile::PLAYER && level[y][x]->getType() != CMap::ATile::EMPTY) || !level[y][x]->canPassThrough(this))
   {
      _position.x += (x * TILESIZE) - _position.x - 0.1;
      x = _position.x / TILESIZE;
   }
   level[y][x]->addEntity(this);
   level[y][x]->getPowerups(this);
   return;
}

void CPlayer::placeExplosive(float const& frametime __attribute__((unused)), CMap& level)
{
   if (_explosiveOnGround >= _explosiveMaxNum)
      return;
   CExplosive *exp = new CExplosive(_explosivePower, 3.f, this);
   CGame::_entities.push_front(exp);
   level[_position.y][_position.x]->addEntity(exp);
   _explosiveOnGround += 1;
   return;
}
