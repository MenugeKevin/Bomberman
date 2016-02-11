//
// CAsset.cpp for Asset in /home/pedous_c/rendu/cpp_bomberman
//
// Made by pedous_c
// Login   <pedous_c@epitech.net>
//
// Started on Thu May 28 16:03:25 2015 pedous_c
// Last update Fri Jun 12 11:42:34 2015 pedous_c
//

#include <iostream>
#include "asset.h"

std::map<std::string, gdl::Model*>	CAsset::_models;
std::map<std::string, gdl::Texture*>	CAsset::_textures;

CAsset::~CAsset()
{
  for (std::map<std::string, gdl::Texture*>::iterator it = _textures.begin(); it != _textures.end(); ++it)
    {
      delete (*it).second;
    }
}

bool		CAsset::addTexture(const std::string &path, const std::string &name)
{
  gdl::Texture	*texture = new gdl::Texture;

  if (texture->load(path) == false)
    {
      std::cout << "can't load " << path << std::endl;
      return false;
    }
  _textures.insert(std::pair<std::string, gdl::Texture *>(name, texture));
  return true;
}

void		CAsset::removeTexture(const std::string &name)
{
  if (_textures.find(name) == _textures.end())
    return ;
  _textures.erase(_textures.find(name));
}

gdl::Texture	*CAsset::getTexture(const std::string &name)
{
  if (_textures.find(name) == _textures.end())
    return 0;
  return ((*_textures.find(name)).second);
}

bool		CAsset::addModel(const std::string &path, const std::string &name)
{
  gdl::Model	*model = new gdl::Model;

  if (model->load(path) == false)
    {
      std::cout << "can't load " << path << std::endl;
      return false;
    }
  _models.insert(std::pair<std::string, gdl::Model *>(name, model));
  return true;
}

void		CAsset::removeModel(const std::string &name)
{
  if (_models.find(name) == _models.end())
    return ;
  _models.erase(_models.find(name));
}

gdl::Model	*CAsset::getModel(const std::string &name)
{
  if (_models.find(name) == _models.end())
    return 0;
  return ((*_models.find(name)).second);
}

bool CAsset::loadAll()
{
  addTexture("./res/bomberman.tga", "Background");
  addTexture("./res/backgroundOption.tga", "BackgroundOption");
  addTexture("./res/One.tga", "Solo");
  addTexture("./res/Multi.tga", "Multi");
  addTexture("./res/Option.tga", "Option");
  addTexture("./res/Quit.tga", "Quit");
  addTexture("./res/Title.tga", "Title");
  addTexture("./res/Cursor.tga", "Cursor");

  addTexture("./res/OptionTools/BackIdle.tga", "backIdle");
  addTexture("./res/OptionTools/BackPressed.tga", "backPressed");

  addTexture("./res/OptionTools/res1Idle.tga", "res1Idle");
  addTexture("./res/OptionTools/res1pressed.tga", "res1Pressed");
  addTexture("./res/OptionTools/res2Idle.tga", "res2Idle");
  addTexture("./res/OptionTools/res2Pressed.tga", "res2Pressed");
  addTexture("./res/OptionTools/res3Idle.tga", "res3Idle");
  addTexture("./res/OptionTools/res3Pressed.tga", "res3Pressed");
  addTexture("./res/OptionTools/res4Idle.tga", "res4Idle");
  addTexture("./res/OptionTools/res4Pressed.tga", "res4Pressed");
  addTexture("./res/OptionTools/res5Idle.tga", "res5Idle");
  addTexture("./res/OptionTools/res5Pressed.tga", "res5Pressed");
  addTexture("./res/OptionTools/res6Idle.tga", "res6Idle");
  addTexture("./res/OptionTools/res6Pressed.tga", "res6Pressed");
  addTexture("./res/OptionTools/res7Idle.tga", "res7Idle");
  addTexture("./res/OptionTools/res7Pressed.tga", "res7Pressed");
  addTexture("./res/OptionTools/res8Idle.tga", "res8Idle");
  addTexture("./res/OptionTools/res8Pressed.tga", "res8Pressed");

  addTexture("./res/UnbWall.tga", "UnbWall");
  addTexture("./res/Ground.tga", "Ground");
  addTexture("./res/explosion.tga", "explose");
  addModel("./LibBomberman_linux_x64/assets/marvin.fbx", "Player");
  addModel("./res/Bomb.fbx", "Bomb");
  return true;
}
