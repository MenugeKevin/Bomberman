#ifndef PLAYER_H_
#define PLAYER_H_

#include <vector>
#include <SdlContext.hh>
#include "entity.h"

class CPlayer : public AEntity
{
public:
  enum EControlType
    {
      PLAYER1,
      PLAYER2
    };
public:
  CPlayer(EControlType);
  ~CPlayer();

  bool	initialize();
  bool	update(gdl::Clock const&, gdl::Input const&, CMap&);
  void	draw(gdl::AShader &shader, gdl::Clock const &clock);
  void   decrementExplosiveNumber();
   void hitByExplosion(AEntity const*);

  inline int    getExplosivePower() const {return _explosivePower;}
  inline void   setExplosivePower(int a) {_explosivePower = a;}

  inline int    getExplosiveNumber() const {return _explosiveMaxNum;}
  inline void   setExplosiveNumber(int a ) {_explosiveMaxNum = a;}

  inline float  getSpeedMultiplier() const {return _speedmultiplier;}
  inline void   setSpeedMultiplier(float a) {_speedmultiplier = a;}

protected:

  void	moveUp(float const&, CMap&);
  void	moveLeft(float const&, CMap&);
  void	moveDown(float const&, CMap&);
  void	moveRight(float const&, CMap&);
  void   placeExplosive(float const&, CMap&);

private:
  int   _explosivePower;
  int   _explosiveMaxNum;
  int   _explosiveOnGround;

  float           _movespeed;
  float           _speedmultiplier;
  EControlType    _controlType;
  gdl::Model*     _model;

  std::vector<SDL_Keycode>	_key;
  std::vector<void (CPlayer::*)(float const&, CMap&)>	_point;
};


#endif //PLAYER_H_
