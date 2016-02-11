/*
 *
 *
 *
 *
 *
 *
 */

#include "UnbreakableWall.hpp"

UnbreakableWall::UnbreakableWall(const glm::vec3& position, gdl::Texture *texture, int size) :
  ATile(UNBREAKABLE_WALL), _texture(texture), _size(size)
{
  _pos.first = position.x * _size;
  _pos.second = position.y * _size;
  this->initialize();
}

bool	UnbreakableWall::initialize()
{
  _geometry.setColor(glm::vec4(0.3, 0.3, 0.3, 1));

  // Face Sol
  _geometry.pushVertex(glm::vec3(_pos.first, _pos.second, 0));
  _geometry.pushVertex(glm::vec3(_pos.first + _size, _pos.second, 0));
  _geometry.pushVertex(glm::vec3(_pos.first + _size, _pos.second + _size, 0));
  _geometry.pushVertex(glm::vec3(_pos.first, _pos.second + _size, 0));

  _geometry.pushUv(glm::vec2(0.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 1.0f));
  _geometry.pushUv(glm::vec2(0.0f, 1.0f));

  // Mur Touchant 0,0
  _geometry.pushVertex(glm::vec3(_pos.first, _pos.second, 0));
  _geometry.pushVertex(glm::vec3(_pos.first, _pos.second, 1));
  _geometry.pushVertex(glm::vec3(_pos.first + _size, _pos.second, 1));
  _geometry.pushVertex(glm::vec3(_pos.first + _size, _pos.second, 0));

  _geometry.pushUv(glm::vec2(0.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 1.0f));
  _geometry.pushUv(glm::vec2(0.0f, 1.0f));

  _geometry.pushVertex(glm::vec3(_pos.first + _size, _pos.second, 0));
  _geometry.pushVertex(glm::vec3(_pos.first + _size, _pos.second, 1));
  _geometry.pushVertex(glm::vec3(_pos.first + _size, _pos.second + _size, 1));
  _geometry.pushVertex(glm::vec3(_pos.first + _size, _pos.second + _size, 0));

  _geometry.pushUv(glm::vec2(0.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 1.0f));
  _geometry.pushUv(glm::vec2(0.0f, 1.0f));

  _geometry.pushVertex(glm::vec3(_pos.first, _pos.second + _size, 0));
  _geometry.pushVertex(glm::vec3(_pos.first, _pos.second + _size, 1));
  _geometry.pushVertex(glm::vec3(_pos.first + _size, _pos.second + _size, 0));
  _geometry.pushVertex(glm::vec3(_pos.first, _pos.second + _size, 0));

  _geometry.pushUv(glm::vec2(0.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 1.0f));
  _geometry.pushUv(glm::vec2(0.0f, 1.0f));

  _geometry.pushVertex(glm::vec3(_pos.first, _pos.second, 0));
  _geometry.pushVertex(glm::vec3(_pos.first, _pos.second, 1));
  _geometry.pushVertex(glm::vec3(_pos.first, _pos.second + _size, 1));
  _geometry.pushVertex(glm::vec3(_pos.first, _pos.second + _size, 0));

  _geometry.pushUv(glm::vec2(0.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 1.0f));
  _geometry.pushUv(glm::vec2(0.0f, 1.0f));

  _geometry.pushVertex(glm::vec3(_pos.first, _pos.second + _size, 0));
  _geometry.pushVertex(glm::vec3(_pos.first, _pos.second + _size, 1));
  _geometry.pushVertex(glm::vec3(_pos.first + _size, _pos.second + _size, 1));
  _geometry.pushVertex(glm::vec3(_pos.first + _size, _pos.second + _size, 0));

  _geometry.pushUv(glm::vec2(0.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 1.0f));
  _geometry.pushUv(glm::vec2(0.0f, 1.0f));

  _geometry.pushVertex(glm::vec3(_pos.first, _pos.second, 1));
  _geometry.pushVertex(glm::vec3(_pos.first + _size, _pos.second, 1));
  _geometry.pushVertex(glm::vec3(_pos.first + _size, _pos.second + _size, 1));
  _geometry.pushVertex(glm::vec3(_pos.first, _pos.second + _size, 1));

  _geometry.pushUv(glm::vec2(0.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 1.0f));
  _geometry.pushUv(glm::vec2(0.0f, 1.0f));

  _geometry.build();
  return (true);
}

bool	UnbreakableWall::update(__attribute__((unused))gdl::Clock const &clock, __attribute__((unused))gdl::Input &input)
{
  return (false);
}

void	UnbreakableWall::draw(gdl::AShader &shader, __attribute__((unused))gdl::Clock const &clock)
{
  _texture->bind();
  _geometry.draw(shader, getTransformation(), GL_QUADS);
}


#include <iostream>
void	UnbreakableWall::draw(gdl::AShader &shader)
{
  _texture->bind();
  _geometry.draw(shader, getTransformation(), GL_QUADS);
}

bool	UnbreakableWall::hitByExplosion(__attribute__((unused))AEntity* entity)
{
  return (true);
}
