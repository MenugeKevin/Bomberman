#include "map.h"
#include "asset.h"
#include "game.h"
#include "explosive.h"
#include "player.h"

CExplosive::CExplosive(int power, float timer, AEntity *parent) :
  AEntity(AEntity::BOMB, parent),
  _power(power),
  _model(CAsset::getModel("Bomb")),
  _explosalive(0.5f)
{
  setLifespawn(timer);
  rotate(glm::vec3(1, 0, 0), 90);
  scale(glm::vec3(0.0025f, 0.0025f, 0.0025f));
  setPosition(parent->getPosition());
}

CExplosive::~CExplosive()
{}

void CExplosive::hitByExplosion(AEntity const *trigger)
{
  if (trigger != this)
    explode();
  return;
}

#include <iostream>

bool CExplosive::update(gdl::Clock const& clock, gdl::Input const& input __attribute__((unused)), CMap&)
{
  float frametime = static_cast<float>(clock.getElapsed());

  if (_temporary)
    {
      _lifespwan -= frametime;
      if (_lifespwan <= 0)
	{
	  schleduleForDeletion();
	  _lifespwan += 1;
	}
    }
  if (_delete)
    {
      explode();
    }
  return true;
}


void CExplosive::draw(gdl::AShader& shader, gdl::Clock const& clock)
{
  _model->draw(shader, getTransformation(), clock.getElapsed());
  return;
}

void	CExplosive::cleanExplosion(gdl::Clock const& clock)
{
  float frametime = static_cast<float>(clock.getElapsed());
  CMap	*level = CGame::getLevel();

  _explosalive -= frametime;
  std::cout << "Destroy" << std::endl;
  for (int i = 0; i < _power; ++i)
    {
      if (_position.x + i > (*level).size())
	break;
      level->destroyTile(_position.y, _position.x + i);
    }
  for (int i = 0; i < _power; ++i)
    {
      if (_position.x - i < 0)
	break;
      level->destroyTile(_position.y, _position.x - i);
    }
  for (int i = 0; i < _power; ++i)
    {
      if (_position.y + i > (*level).size())
	break;
      level->destroyTile(_position.y + i, _position.x);
    }
  for (int i = 0; i < _power; ++i)
    {
      if (_position.y - i < 0)
	break;
      level->destroyTile(_position.y - i, _position.x);
    }

}


void CExplosive::explode()
{
  CMap *level= CGame::getLevel();


  (*level)[_position.y][_position.x]->explodeEntity(this);
  for (int i = 0; i < _power; ++i)
    {
      if (_position.x + i > (*level).size())
	break;

      if ((*level)[_position.y][_position.x + i]->getType() != CMap::ATile::EMPTY && (*level)[_position.y][_position.x + i]->getType() != CMap::ATile::PLAYER)
	{
	  (*level)[_position.y][_position.x + i]->hitByExplosion(this);
	  level->destroyTile(_position.y, _position.x + i);
	  level->createExplosionTile(_position.y, _position.x + i);
	  break;
	}
      (*level)[_position.y][_position.x + i]->explodeEntity(this);
      level->createExplosionTile(_position.y, _position.x + i);
    }
  for (int i = 1; i < _power; ++i)
    {
      if (_position.x - i < 0)
	break;
      if ((*level)[_position.y][_position.x - i]->getType() != CMap::ATile::EMPTY && (*level)[_position.y][_position.x - i]->getType() != CMap::ATile::PLAYER)
	{
	  (*level)[_position.y][_position.x - i]->hitByExplosion(this);
	  level->destroyTile(_position.y, _position.x - i);
	  level->createExplosionTile(_position.y, _position.x - i);
	  break;
	}

      (*level)[_position.y][_position.x - i]->explodeEntity(this);
      level->createExplosionTile(_position.y, _position.x - i);
    }
  for (int i = 1; i < _power; ++i)
    {
      if (_position.y + i > (*level).size())
	break;
      if ((*level)[_position.y + i][_position.x]->getType() != CMap::ATile::EMPTY && (*level)[_position.y + i][_position.x]->getType() != CMap::ATile::PLAYER)
	{
	  (*level)[_position.y + i][_position.x]->hitByExplosion(this);
	  level->destroyTile(_position.y + i, _position.x);
	  level->createExplosionTile(_position.y + i, _position.x);
	  break;
	}
      (*level)[_position.y + i][_position.x]->explodeEntity(this);
      level->createExplosionTile(_position.y + i, _position.x);
    }
  for (int i = 1; i < _power; ++i)
    {
      if (_position.y - i < 0)
	break;

      if ((*level)[_position.y - i][_position.x]->getType() != CMap::ATile::EMPTY && (*level)[_position.y - i][_position.x]->getType() != CMap::ATile::PLAYER)
	{
	  (*level)[_position.y - i][_position.x]->hitByExplosion(this);
	  level->destroyTile(_position.y - i, _position.x);
	  level->createExplosionTile(_position.y - i, _position.x);
	  break;
	}
      (*level)[_position.y - i][_position.x]->explodeEntity(this);
      level->createExplosionTile(_position.y - i, _position.x);
    }
  static_cast<CPlayer*>(_parent)->decrementExplosiveNumber();
  return;
}
