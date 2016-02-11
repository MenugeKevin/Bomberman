//
// button.cpp for button in /home/pedous_c/rendu/cpp_bomberman
// 
// Made by pedous_c
// Login   <pedous_c@epitech.net>
// 
// Started on Thu Jun 11 12:17:07 2015 pedous_c
// Last update Fri Jun 12 13:01:15 2015 pedous_c
//

#include "button.hpp"
#include <iostream>

CButton::CButton(const glm::vec3 &position, const glm::vec2 &size, gdl::Texture *texture, void (*buttonAction)(void)) : ABaseObject() , _texture(texture), _buttonAction(buttonAction)
{
  _position = position;
  this->initialize(size);
}

CButton::~CButton()
{

}

bool	CButton::initialize(const glm::vec2 &size)
{
  _geometry.pushVertex(glm::vec3(_position.x, _position.y, _position.z));
  _geometry.pushVertex(glm::vec3(_position.x + size.x, _position.y, _position.z));
  _geometry.pushVertex(glm::vec3(_position.x + size.x, _position.y + size.y, _position.z));
  _geometry.pushVertex(glm::vec3(_position.x, _position.y + size.y, _position.z));

  _geometry.pushUv(glm::vec2(0.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 1.0f));
  _geometry.pushUv(glm::vec2(0.0f, 1.0f));

  _geometry.build();
  return (true);
}

bool	CButton::update(gdl::Clock const &clock __attribute__((unused)), const gdl::Input &input __attribute__((unused)))
{
  return false;
}

void	CButton::draw(gdl::AShader &shader, gdl::Clock const &clock __attribute__((unused)))
{
  _texture->bind();
  _geometry.draw(shader, getTransformation(), GL_QUADS);
}

int	CButton::OnClick()
{
  (*_buttonAction)();
  return (0);
}

void	CButton::setPosition(const glm::vec3 &position)
{
  _position = position;
}

void	CButton::setTexture(gdl::Texture *texture)
{
  _texture = texture;
}
