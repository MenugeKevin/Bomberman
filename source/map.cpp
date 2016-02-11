#include <fstream>
#include "map.h"
#include "asset.h"
#include "UnbreakableWall.hpp"
#include "BreakableWall.hpp"
#include "EmptyWall.hpp"
#include "ExplosionWall.hpp"
#include "game.h"

CMap::CMap(int nbplayer, int height, int width) :
  _maxPlayer(nbplayer)
{
  generate(width, height, "cool");
}

CMap::CMap(std::string const& level)
{
   load(level);
}

CMap::~CMap()
{
   for (unsigned int i = 0; i < _level.size(); ++i)
   {
      for (unsigned int j = 0; i < _level[i].size(); ++j)
      {
	 if (_level[i][j])
	    delete _level[i][j];
      }
   }
}

std::vector<CMap::ATile*>& CMap::operator[](int index)
{
   return _level[index];
}

int CMap::size() const
{
   return _level.size();
}

CMap::ATile *CMap::getTile(int x, int y) const
{
   if (x < 0 || y < 0 || static_cast<unsigned>(y) > _level.size())
      return 0;
   if (static_cast<unsigned>(x) > _level[y].size())
      return 0;
   return _level[y][x];
}

void CMap::draw(gdl::AShader& shader)
{
   for (unsigned int y = 0; y < _level.size(); ++y)
   {
      for (unsigned int x = 0; x < _level[y].size(); ++x)
	 _level[y][x]->draw(shader);
   }
}

bool  CMap::load(std::string const& level)
{
   //TODO load level from params
   //std::ifstream is;
   (void) level;
   return true;
}

// TODO generate a new map then play it
bool	CMap::detectPlayer(int y, int x)
{
  for (int i = y - 3; i < y + 3; ++i)
    {
      for (int j = x - 3; j < x + 3 ; ++j)
	{
	  if (j > 0 && i > 0 && static_cast<unsigned>(j) < _level[i].size()  && static_cast<unsigned>(i) < _level.size())
	    {
	      if (_level[i][j]->getType() == ATile::PLAYER)
		return (false);
	    }
	}
    }
  return (true);
}

void	CMap::destroyEverything(int y, int x)
{
    for (int i = y - 3; i < y + 3 ; ++i)
    {
      for (int j = x - 3; j < x + 3; ++j)
	{

	  if (j > 0 && i > 0 && static_cast<unsigned>(i) < _level.size()  && static_cast<unsigned>(j) < _level[i].size())
	    {
	      if (_level[i][j]->getType() == ATile::BREAKABLE_WALL)
		{
		  delete _level[i][j];
		  _level[i][j] = new EmptyWall(glm::vec3(j, i, 0), CAsset::getTexture("Ground"), TILESIZE);
		}
	    }
	}
    }
}

bool CMap::generate(int width, int height, std::string const& name)
{
  _name = name;
  for (int i = 0; i < height; ++i)
    {
      std::vector<ATile*> tmp;
      for (int j = 0; j < width; ++j)
	{
	  if ((i == 0 || j == 0 || j == width - 1 || i == height - 1) || (i % 2 == 0 && j % 2 == 0))
	    {
	      tmp.push_back(new UnbreakableWall(glm::vec3(j, i, 0), CAsset::getTexture("UnbWall"), TILESIZE));
	    }
	  else
	    {
	      tmp.push_back(new EmptyWall(glm::vec3(j, i, 0), CAsset::getTexture("Ground"), TILESIZE));
	    }
	}
      _level.push_back(tmp);
    }

  for (int i = 0; i < height; ++i)
    {
      for (int j = 0; j < width; ++j)
	{
	  if (((rand() % 10) % 2) && (_level[i][j]->getType() == ATile::EMPTY))
	    {
	      delete _level[i][j];
	      _level[i][j] = new BreakableWall(glm::vec3(j, i, 0), CAsset::getTexture("UnbWall"), TILESIZE);
	    }
	}
    }

  int nb = 0;
  for (int i = 0; i < height && nb < _maxPlayer; ++i)
    {
      for (int j = 0; j < width && nb < _maxPlayer; ++j)
	{
	  if (j > 0 && i > 0)
	    {
	      if (_level[i][j]->getType() == ATile::EMPTY && detectPlayer(i, j))
		{
		  nb++;
		  _level[i][j]->setType(ATile::PLAYER);
		  destroyEverything(i, j);
		}
	    }
	}
    }
  return 0;
}

void	CMap::destroyTile(int i, int j)
{
  if (_level[i][j]->getType() != ATile::UNBREAKABLE_WALL)
    {
      delete _level[i][j];
      _level[i][j] = new EmptyWall(glm::vec3(j, i, 0), CAsset::getTexture("Ground"), TILESIZE);
    }
}

void	CMap::createExplosionTile(int i, int j)
{
  if (_level[i][j]->getType() != ATile::UNBREAKABLE_WALL)
    {
      ExplosionWall *tmp = new ExplosionWall(glm::vec3(j, i, 0), CAsset::getTexture("explose"), TILESIZE);
      CGame::_entities.push_front(tmp);
    }
}
