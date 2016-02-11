/*
 *
 *
 *
 *
 *
 */

#ifndef EMPTYWALL_HPP_
# define EMPTYWALL_HPP_

# include <Geometry.hh>
# include <Texture.hh>
# include "map.h"

class EmptyWall : public CMap::ATile {
public:
  EmptyWall(const glm::vec3&, gdl::Texture*, int);
  ~EmptyWall() {}
  bool	initialize();
  bool	update(gdl::Clock const &clock, gdl::Input &input);
  void	draw(gdl::AShader &shader, gdl::Clock const &clock);
  void	draw(gdl::AShader &);

  bool	hitByExplosion(AEntity *);
private:
  gdl::Geometry	_geometry;
  gdl::Texture	*_texture;
  std::pair<float, float>	_pos;
  int			_size;
};

#endif // EMPTYWALL_HPP_
