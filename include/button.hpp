//
// button.hpp for button in /home/pedous_c/rendu/cpp_bomberman
// 
// Made by pedous_c
// Login   <pedous_c@epitech.net>
// 
// Started on Thu Jun 11 12:17:34 2015 pedous_c
// Last update Fri Jun 12 13:01:30 2015 pedous_c
//

#ifndef BUTTON_H_
# define BUTTON_H_

# include <baseobject.h>
# include <Texture.hh>
# include <Geometry.hh>

class CButton : public ABaseObject
{
private:
  gdl::Texture	*_texture;
  gdl::Geometry	_geometry;
  void		(*_buttonAction)(void);
public:
  CButton(const glm::vec3&, const glm::vec2&, gdl::Texture*, void (*buttonAction)(void));
  ~CButton();
  bool	initialize(const glm::vec2 &size);
  bool	update(gdl::Clock const &clock __attribute__((unused)), const gdl::Input &input __attribute__((unused)));
  void	draw(gdl::AShader &shader, gdl::Clock const &clock __attribute__((unused)));
  int	OnClick();
  void	setPosition(const glm::vec3 &position);
  void	setTexture(gdl::Texture *texture);
};

#endif /*!BUTTON_H_*/
