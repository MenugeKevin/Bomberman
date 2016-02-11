#ifndef POWERUP_H_
#define POWERUP_H_

#include "entity.h"

class CPlayer;

class CPowerup : public AEntity
{
   public:
      enum EType
      {
         SKULL,
         GOLDEN_FLAME,
         MOVE_SPEED_UP,
         MOVE_SPEED_DOWN,
         EXPLOSIVE_POWER_UP,
         EXPLOSIVE_POWER_DOWN,
         EXPLOSIVE_NUMBER_UP,
         EXPLOSIVE_NUMBER_DOWN,
      };
   public:
      CPowerup(EType);
      ~CPowerup();

      void draw(gdl::AShader&);
      bool update(gdl::Clock const&, gdl::Input const&, CMap&);
      void hitByExplosion(AEntity const*);
      void taken(CPlayer *);


   private:
      EType _type;
};

#endif //POWERUP_H_
