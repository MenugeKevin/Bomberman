/*
 *
 *
 *
 *
 *
 */

#ifndef UNBREAKABLEWALL_HPP_
# define UNBREAKABLEWALL_HPP_

# include <Geometry.hh>
# include <Texture.hh>
# include "map.h"

class UnbreakableWall : public CMap::ATile {
public:
  UnbreakableWall(const glm::vec3&, gdl::Texture *, int);
  ~UnbreakableWall() {}
  bool	initialize();
  bool	update(gdl::Clock const &clock, gdl::Input &input);
  void	draw(gdl::AShader &shader, gdl::Clock const &clock);
  void	draw(gdl::AShader &);

  bool	hitByExplosion(AEntity*);
private:
  gdl::Geometry	_geometry;
  gdl::Texture	*_texture;
  std::pair<float, float>	_pos;
  int		_size;
};

#endif // UNBREAKABLEWALL_HPP_
