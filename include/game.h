#ifndef GAME_H_
#define GAME_H_

#include <list>
#include "gamescene.h"

class CMap;
class AEntity;
class CPlayer;
class CCamera;

class CGame : public IGameScene
{
   public:
      CGame(bool, int, glm::vec2 const&);
      ~CGame();

      inline bool isReady() const {return _ready;}
      void draw(gdl::AShader&, gdl::Clock const&);
      bool update(gdl::Clock const&, gdl::Input const&);
      static CMap *getLevel();

      static CMap          *_level;
      static std::list<AEntity*>  _entities;

   protected:
      void spawnPlayers();
      void win();

   private:
      bool                 _ready;
      CCamera*             _camera;
      CPlayer*             _players[2];
      std::list<CPlayer*>  _playerslist;
};

#endif //GAME_H_
