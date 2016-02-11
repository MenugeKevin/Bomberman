/*
 *
 *
 *
 *
 *
 */

#ifndef EXPLOSIONWALL_HPP_
# define EXPLOSIONWALL_HPP_

# include <Geometry.hh>
# include <Texture.hh>
# include "map.h"
//# include "entity.h"

class ExplosionWall : public CMap::ATile , public AEntity {
public:
  ExplosionWall(const glm::vec3&, gdl::Texture*, int);
  ~ExplosionWall() {}
  bool	initialize();
  bool	update(gdl::Clock const &clock, gdl::Input &input);
  void	draw(gdl::AShader &shader, gdl::Clock const &clock);
  void	draw(gdl::AShader &);

  bool update(gdl::Clock const&, gdl::Input const&, CMap&);
  bool hitByExplosion(AEntity *);
  void hitByExplosion(AEntity const*);
private:
  gdl::Geometry	_geometry;
  gdl::Texture	*_texture;
  std::pair<float, float>	_pos;
  int		_size;
};

#endif // EXPLOSIONWALL_HPP_
