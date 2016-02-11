#include "map.h"
#include "player.h"
#include "powerup.h"

CMap::ATile::ATile(EType type) :
   _type(type)
{}

CMap::ATile::~ATile()
{}

void CMap::ATile::addEntity(AEntity *entity)
{
   if (!entity)
      return;
   _entities.push_front(entity);
   return;
}

void CMap::ATile::removeEntity(AEntity *entity)
{
   for (std::list<AEntity*>::iterator it = _entities.begin(); it != _entities.end(); ++it)
   {
      if (*it == entity)
      {
         _entities.erase(it);
         return;
      }
   }
   return;
}

void CMap::ATile::explodeEntity(AEntity *trigger)
{
   for (std::list<AEntity*>::iterator it = _entities.begin(); it != _entities.end(); ++it)
      (*it)->hitByExplosion(trigger);
   return;
}

bool CMap::ATile::canPassThrough(CPlayer const* parent)
{
   for (std::list<AEntity*>::iterator it = _entities.begin(); it != _entities.end(); ++it)
   {
      if (parent == (*it)->getParent())
         continue;
      if ((*it)->getType() == AEntity::BOMB)
      {
         if ((*it)->getType() == AEntity::PLAYER)
         {
            if (!(static_cast<CPlayer*>(*it)->isAlive()))
               continue;
         }
         return false;
      }
   }
   return true;
}

void CMap::ATile::getPowerups(CPlayer *target)
{
   for (std::list<AEntity*>::iterator it = _entities.begin(); it != _entities.end(); ++it)
   {
      if ((*it)->getType() == AEntity::POWERUP)
         (static_cast<CPowerup*>(*it))->taken(target);
   }
   return;
}
