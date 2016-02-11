#include "player.h"
#include "powerup.h"

CPowerup::CPowerup(EType type) :
   AEntity(POWERUP),
   _type(type)
{
   setLifespawn(15.f);
}

CPowerup::~CPowerup()
{}

void CPowerup::draw(gdl::AShader& shader)
{
   //MODEL
   (void) shader;
   return;
}

void CPowerup::hitByExplosion(AEntity const* trigger __attribute__((unused)))
{
   schleduleForDeletion();
   return;
}

bool CPowerup::update(gdl::Clock const& clock, gdl::Input const&, CMap& level __attribute__((unused)))
{
   float frametime = static_cast<float>(clock.getElapsed());

   if (_temporary)
   {
      _lifespwan -= frametime;
      if (_lifespwan <= 0)
	 schleduleForDeletion();
   }
   return true;
}

void CPowerup::taken(CPlayer *target)
{
   schleduleForDeletion();
   switch (_type)
   {
      case (SKULL) :
      {
         target->alive(false);
         break;
      }
      case (GOLDEN_FLAME) :
      {
         target->setExplosivePower(20);
         break;
      }
      case (MOVE_SPEED_UP) :
      {
         if (target->getSpeedMultiplier() < 1.5f)
         target->setSpeedMultiplier(target->getSpeedMultiplier() + 0.1f);
         break;
      }
      case (MOVE_SPEED_DOWN) :
      {
         if (target->getSpeedMultiplier() > 0.5f)
         target->setSpeedMultiplier(target->getSpeedMultiplier() - 0.1f);
         break;
      }
      case (EXPLOSIVE_POWER_UP) :
      {
         if (target->getExplosivePower() < 8)
            target->setExplosivePower(target->getExplosivePower() + 1);
         break;
      }
      case (EXPLOSIVE_POWER_DOWN) :
      {
         if (target->getExplosivePower() > 2)
            target->setExplosivePower(target->getExplosivePower() + 1);
         break;
      }
      case (EXPLOSIVE_NUMBER_UP) :
      {
         target->setExplosiveNumber(target->getExplosiveNumber() + 1);
         break;
      }
      case (EXPLOSIVE_NUMBER_DOWN) :
      {
         if (target->getExplosiveNumber() > 1)
            target->setExplosiveNumber(target->getExplosiveNumber() - 1);
         break;
      }
      default:
         break;
   }
   return;
}
