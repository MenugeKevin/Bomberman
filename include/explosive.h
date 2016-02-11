#ifndef EXPLOSIVE_H_
#define EXPLOSIVE_H_

#include "entity.h"

class CExplosive : public AEntity
{
   public:
      CExplosive(int, float, AEntity *);
      ~CExplosive();

      void draw(gdl::AShader&, gdl::Clock const&);
      bool update(gdl::Clock const&, gdl::Input const&, CMap&);
      void hitByExplosion(AEntity const*);

   private:
      void explode();
      void cleanExplosion(gdl::Clock const& clock);
      int         _power;
      gdl::Model* _model;
      float	  _explosalive;
};

#endif //EXPLOSIVE_H_
