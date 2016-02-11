/*
 *
 *
 *
 *
 *
 *
 */

#include "EmptyWall.hpp"

EmptyWall::EmptyWall(const glm::vec3& pos, gdl::Texture *texture, int size) :
  ATile(EMPTY), _texture(texture), _size(size)
{
  _pos.first = pos.x * _size;
  _pos.second = pos.y * _size;
  initialize();

}

bool	EmptyWall::initialize()
{
  _geometry.setColor(glm::vec4(0.3, 0.3, 0.3, 1));
  _geometry.pushVertex(glm::vec3(_pos.first, _pos.second, 0));
  _geometry.pushVertex(glm::vec3(_pos.first + _size, _pos.second, 0));
  _geometry.pushVertex(glm::vec3(_pos.first + _size, _pos.second + _size, 0));
  _geometry.pushVertex(glm::vec3(_pos.first, _pos.second + _size, 0));

  _geometry.pushUv(glm::vec2(0.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 1.0f));
  _geometry.pushUv(glm::vec2(0.0f, 1.0f));

  _geometry.build();
  return (true);
}

bool	EmptyWall::update(__attribute__((unused))gdl::Clock const &clock, __attribute__((unused))gdl::Input &input)
{
  return (false);
}

void	EmptyWall::draw(gdl::AShader &shader, __attribute__((unused))gdl::Clock const &clock)
{
  _texture->bind();
  _geometry.draw(shader, getTransformation(), GL_QUADS);
}

void	EmptyWall::draw(gdl::AShader &shader)
{
  _texture->bind();
  _geometry.draw(shader, getTransformation(), GL_QUADS);
}

bool	EmptyWall::hitByExplosion(__attribute__((unused))AEntity *entity)
{
  return (true);
}
