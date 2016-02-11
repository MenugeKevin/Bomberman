#ifndef GAMEENGINE_H_
#define GAMEENGINE_H_

#include <glm/glm.hpp>
#include <SdlContext.hh>
#include <BasicShader.hh>
#include "scenemanager.h"

class CGameEngine : public CSceneManager
{
   public:
      CGameEngine();
      ~CGameEngine();

      bool  init();
      void  loop();

      static float   getMusicVolume();
      static float   getMasterVolume();

      static void    setMusicVolume(float const&);
      static void    setMasterVolume(float const&);
      static void    resizeWindow(glm::vec2 const&);

      static glm::vec2 const&   getWindowSize();

      static bool    _quitApplication;

      static int	   _nbAI;
      static glm::vec2     _mapSize;
   private:
      static float      _volume;
      static float      _musicVolume;

      static glm::vec2 _windowSize;

      static gdl::SdlContext   _context;
      static gdl::BasicShader  _shader;
};

#endif //GAMEENGINE_H_
