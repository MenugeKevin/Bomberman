#ifndef ENTITY_H_
#define ENTITY_H_

#include <Model.hh>
#include "baseobject.h"

class CMap;

class AEntity : public ABaseObject
{
   public:
      enum EType
      {
	 UNDEFINED,
	 BOMB,
	 PLAYER,
	 CAMERA,
	 POWERUP,
	 EXPLOSION
      };
   public:
      ~AEntity();

      virtual bool update(gdl::Clock const&, gdl::Input const&, CMap&) = 0;
      virtual void hitByExplosion(AEntity const*) = 0;

      void  alive(bool);
      bool  isAlive() const;

      bool isDeletable() const;
      void schleduleForDeletion();

      void setLifespawn(float const&);

      void setParent(AEntity *);
      AEntity const *getParent() const;

      EType getType() const;

      glm::vec3 const&	getPosition() const;
      void	setPosition(glm::vec3 const&);

      glm::vec3 const&	getAngle() const;
      void	setAngle(glm::vec3 const&);
   protected:
      AEntity(EType, AEntity * = 0);

      bool     _alive;
      bool     _delete;
      bool     _temporary;
      float    _lifespwan;
      EType    _type;
      AEntity  *_parent;
};

#endif //ENTITY_H_
