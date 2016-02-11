//
// menu.hpp for menu in /home/pedous_c/rendu/cpp_bomberman
//
// Made by pedous_c
// Login   <pedous_c@epitech.net>
//
// Started on Wed Jun 10 13:16:39 2015 pedous_c
// Last update Sat Jun 13 13:41:06 2015 pedous_c
//

#ifndef MENU_H_
# define MENU_H_

# include <vector>
# include <baseobject.h>
# include <OpenGL.hh>
# include <Input.hh>
# include <SdlContext.hh>
# include "gamescene.h"
# include "button.hpp"

class CCamera;

class CMenu : public IGameScene
{
private:
  std::vector<CButton *>	_choose;
  std::vector<CButton *>	_tools;
  glm::vec3			_moveCursor[4];
  int				_count;
  int				_index;
  int				_countUp;
  int				_countDown;
  CCamera*			_cameraMenu;
public:
  CMenu();
  ~CMenu();
  bool			initialize();
  bool			update(gdl::Clock const &clock, const gdl::Input &input);
  void			draw(gdl::AShader &shader, gdl::Clock const &clock);
  void			OnUp();
  void			OnDown();
};

#endif /*!MENU_H_*/
