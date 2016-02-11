#ifndef SCENEMANAGER_H_
#define SCENEMANAGER_H_

#include <list>
#include <string>

class IGameScene;

class CSceneManager
{
   public:
      CSceneManager();
      ~CSceneManager();

      static bool addScene(IGameScene*, std::string const&, bool = true);
      static bool removeScene(std::string const&);
      static bool setActiveScene(std::string const&);
      static IGameScene *getActiveScene(void);

   protected:
      static IGameScene *_activeScene;
      static std::list<std::pair<IGameScene*, std::string> > _scenes;
};

#endif //SCENEMANEGER_H_
