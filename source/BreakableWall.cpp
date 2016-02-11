/*
 *
 *
 *
 *
 *
 *
 */

#include "BreakableWall.hpp"

BreakableWall::BreakableWall(const glm::vec3& pos, gdl::Texture* texture, int size) :
  ATile(BREAKABLE_WALL), _texture(texture), _size(size)
{
  _pos.first = pos.x * _size;
  _pos.second = pos.y * _size;
  initialize();
}

bool	BreakableWall::initialize()
{
  _geometry.setColor(glm::vec4(0.8, 1, 1, 1));

  _geometry.pushVertex(glm::vec3(_pos.first, _pos.second, 0));
  _geometry.pushVertex(glm::vec3(_pos.first + _size, _pos.second, 0));
  _geometry.pushVertex(glm::vec3(_pos.first + _size, _pos.second + _size, 0));
  _geometry.pushVertex(glm::vec3(_pos.first, _pos.second + _size, 0));

  _geometry.pushUv(glm::vec2(0.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 1.0f));
  _geometry.pushUv(glm::vec2(0.0f, 1.0f));

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

bool	BreakableWall::update(__attribute__((unused))gdl::Clock const &clock, __attribute__((unused))gdl::Input &input)
{
  return (false);
}

void	BreakableWall::draw(gdl::AShader &shader, __attribute__((unused))gdl::Clock const &clock)
{
  _texture->bind();
  _geometry.draw(shader, getTransformation(), GL_QUADS);
}

void	BreakableWall::draw(gdl::AShader &shader)
{
  _texture->bind();
  _geometry.draw(shader, getTransformation(), GL_QUADS);
}

bool	BreakableWall::hitByExplosion(__attribute__((unused))AEntity *entity)
{
  return (true);
}
