#include "entity.h"

AEntity::AEntity(EType type, AEntity *parent) :
   ABaseObject(),
   _alive(true),
   _delete(false),
   _temporary(false),
   _lifespwan(0),
   _type(type),
   _parent(parent)
{}

AEntity::~AEntity()
{}

AEntity::EType AEntity::getType() const
{
   return _type;
}

void AEntity::alive(bool alive)
{
   _alive = alive;
   return;
}

bool AEntity::isAlive() const
{
   return _alive;
}

void AEntity::setParent(AEntity *parent)
{
   _parent = parent;
   return;
}

AEntity const* AEntity::getParent() const
{
   return _parent;
}

bool AEntity::isDeletable() const
{
   return _delete;
}

void AEntity::schleduleForDeletion()
{
   _delete = true;
   return;
}

void AEntity::setLifespawn(float const& lifespwan)
{
   _temporary = true;
   _lifespwan = lifespwan;
   return;
}

glm::vec3 const&	AEntity::getPosition() const
{
  return (_position);
}


void		AEntity::setPosition(glm::vec3 const& pos)
{
  _position = pos;
}


glm::vec3 const&	AEntity::getAngle() const
{
  return (_rotation);
}


void		AEntity::setAngle(glm::vec3 const& rotation)
{
  _rotation = rotation;
}
