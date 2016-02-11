#ifndef CAMERA_H_
#define CAMERA_H_

#include "entity.h"

class CCamera : public AEntity
{
public:
  CCamera(glm::vec3 const& = glm::vec3(0, 10, 30), glm::vec3 const& = glm::vec3(0, 0, 0), float const& = 90);
  ~CCamera();

  glm::mat4 const& getProjection() const;
  glm::mat4 const& getTransformation() const;
  void	draw(gdl::AShader &shader, gdl::Clock const &clock);
   bool update(gdl::Clock const&, gdl::Input const&, CMap&);

  void	hitByExplosion(AEntity const*);
private:
  float		_fov;
  glm::vec3	_lookat;
  glm::mat4	_projection;
  glm::mat4	_transformation;
  glm::vec2	_winsize;
};

#endif //CAMERA_H_
