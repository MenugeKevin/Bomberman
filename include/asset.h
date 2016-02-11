//
// Asset.hpp for Asset in /home/pedous_c/rendu/cpp_bomberman
//
// Made by pedous_c
// Login   <pedous_c@epitech.net>
//
// Started on Thu May 28 16:02:54 2015 pedous_c
// Last update Fri May 29 13:37:00 2015 pedous_c
//

#ifndef ASSET_H_
# define ASSET_H_

# include <map>
# include <Texture.hh>
# include <Model.hh>

class CAsset
{
public:
  CAsset(){}
  ~CAsset();

  bool         loadAll();

  static bool  addTexture(const std::string&, const std::string&);
  static void	removeTexture(const std::string&);
  static gdl::Texture	*getTexture(const std::string&);

  static bool		addModel(const std::string &, const std::string &);
  static void		removeModel(const std::string &);
  static gdl::Model	*getModel(const std::string &);

  static std::map<std::string, gdl::Texture*>	_textures;
  static std::map<std::string, gdl::Model*>	_models;
};

#endif /*!ASSET_H_*/
