//
// option.hpp for option in /home/pedous_c/rendu/cpp_bomberman
// 
// Made by pedous_c
// Login   <pedous_c@epitech.net>
// 
// Started on Fri Jun 12 09:42:59 2015 pedous_c
// Last update Fri Jun 12 14:20:45 2015 pedous_c
//

#ifndef OPTION_H_
# define OPTION_H_

# include <vector>
# include <Texture.hh>
# include <baseobject.h>
# include <OpenGL.hh>
# include <Input.hh>
# include <SdlContext.hh>
# include "gamescene.h"

class CCamera;
class CButton;

class COption : public IGameScene
{
private:
  bool				_enter;
  int				_count;
  int				_index;
  int				_save;
  int				_countUp;
  int				_countDown;
  std::vector<glm::vec2>	_resolution;
  std::vector<CButton *>	_choose;
  std::vector<gdl::Texture *>	_change;
  std::vector<gdl::Texture *>	_change2;
  CButton			*_background;
  CCamera*			_cameraOption;
public:
  COption();
  ~COption();
  bool	initialize();
  bool	update(gdl::Clock const &clock, const gdl::Input &input);
  void	draw(gdl::AShader &shader, gdl::Clock const &clock);
  void	OnUp();
  void	OnDown();
};

#endif /*!OPTION_H_*/
