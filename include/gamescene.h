#ifndef GAMESCENE_H_
#define GAMESCENE_H_

namespace gdl
{
   class Clock;
   class Input;
   class AShader;
};

class IGameScene
{
   public:
      virtual ~IGameScene() {}

      virtual void   draw(gdl::AShader&, const gdl::Clock&) = 0;
      virtual bool   update(gdl::Clock const&, gdl::Input const&) = 0;
};

#endif //GAMESCENE_H_
