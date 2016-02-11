/*
 *
 *
 *
 *
 *
 *
 */

#include "ExplosionWall.hpp"

ExplosionWall::ExplosionWall(const glm::vec3& pos, gdl::Texture* texture, int size) :
  ATile(EMPTY), AEntity(EXPLOSION), _texture(texture), _size(size)
{
  setLifespawn(0.25f);
  _pos.first = pos.x * _size;
  _pos.second = pos.y * _size;
  initialize();
}

bool	ExplosionWall::initialize()
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

bool	ExplosionWall::update(__attribute__((unused))gdl::Clock const &clock, __attribute__((unused))gdl::Input &input)
{
  return (false);
}

void	ExplosionWall::draw(gdl::AShader &shader, __attribute__((unused))gdl::Clock const &clock)
{
  _texture->bind();
  _geometry.draw(shader, ATile::getTransformation(), GL_QUADS);
}

void	ExplosionWall::draw(gdl::AShader &shader)
{
  _texture->bind();
  _geometry.draw(shader, ATile::getTransformation(), GL_QUADS);
}

bool	ExplosionWall::hitByExplosion(__attribute__((unused))AEntity *entity)
{
  return (true);
}

void	ExplosionWall::hitByExplosion(__attribute__((unused))AEntity const* entity)
{
}

bool	ExplosionWall::update(gdl::Clock const& clock, gdl::Input const& input __attribute__((unused)), CMap&)
{
  float frametime = static_cast<float>(clock.getElapsed());

  if (_temporary)
    {
      _lifespwan -= frametime;
      if (_lifespwan <= 0)
	{
	  schleduleForDeletion();
	  _lifespwan += 1;
	}
    }
  return true;
}
