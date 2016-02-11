#ifndef BASEOBJECT_H_
# define BASEOBJECT_H_

# include <glm/glm.hpp>
# include <glm/gtc/matrix_transform.hpp>
# include <SdlContext.hh>
# include <BasicShader.hh>

class ABaseObject
{
   public:
      virtual	~ABaseObject();
      virtual bool	initialize();
      virtual void	draw(gdl::AShader&, gdl::Clock const&) = 0;
      virtual bool   update(gdl::Clock const&, gdl::Input const& input);

      void		translate(glm::vec3 const &v);
      void		rotate(glm::vec3 const& axis, float angle);
      void		scale(glm::vec3 const& scale);
      glm::mat4	getTransformation();

   protected:
      ABaseObject();

      glm::vec3	_position;
      glm::vec3	_rotation;
      glm::vec3	_scale;
};

#endif /*!AOBJECT_H_*/
