#include "baseobject.h"

ABaseObject::ABaseObject() : _position(0, 0, 0), _rotation(0, 0, 0), _scale(1, 1, 1)
{}

ABaseObject::~ABaseObject()
{}

bool	ABaseObject::initialize()
{
  return (true);
}

bool ABaseObject::update(gdl::Clock const& clock __attribute__((unused)), gdl::Input const& input __attribute__((unused)))
{
   return true;
}

void	ABaseObject::translate(glm::vec3 const &v)
{
  _position += v;
  return;
}

void	ABaseObject::rotate(glm::vec3 const& axis, float angle)
{
  _rotation += axis * angle;
  return;
}

void	ABaseObject::scale(glm::vec3 const& scale)
{
  _scale *= scale;
  return;
}

glm::mat4	ABaseObject::getTransformation()
{
  glm::mat4	transform(1);

  transform = glm::translate(transform, _position);
  transform = glm::rotate(transform, _rotation.x, glm::vec3(1, 0, 0));
  transform = glm::rotate(transform, _rotation.y, glm::vec3(0, 1, 0));
  transform = glm::rotate(transform, _rotation.z, glm::vec3(0, 0, 1));
  transform = glm::scale(transform, _scale);
  return (transform);
}
