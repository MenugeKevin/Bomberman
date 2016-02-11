#include "camera.h"
#include "gameengine.h"

CCamera::CCamera(glm::vec3 const& position, glm::vec3 const& lookat, float const& fov) :
   AEntity(CAMERA, 0),
   _fov(fov),
   _lookat(lookat)
{
  _winsize = CGameEngine::getWindowSize();
  _position = position;
  _projection = glm::perspective(_fov, _winsize.x / _winsize.y, 0.1f, 100.f);
  _transformation = glm::lookAt(_position, _lookat, glm::vec3(0, 1, 0));
}

CCamera::~CCamera()
{}

bool CCamera::update(gdl::Clock const& __attribute__((unused)), gdl::Input const& __attribute__((unused)), CMap& __attribute__((unused)))
{
   if (_parent)
   {
      setPosition(glm::vec3(_parent->getPosition().x, _parent->getPosition().y, _position.z));
      _transformation = glm::lookAt(_position, _parent->getPosition(), glm::vec3(0, 1, 0));
   }
   return true;
}


glm::mat4 const& CCamera::getProjection() const
{
   return _projection;
}

glm::mat4 const& CCamera::getTransformation() const
{
   return _transformation;
}

void	CCamera::draw(__attribute__((unused))gdl::AShader &shader, __attribute__((unused))gdl::Clock const &clock)
{
   return;
}

void	CCamera::hitByExplosion(AEntity const*)
{
   return;
}
