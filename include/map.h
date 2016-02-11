#ifndef MAP_H_
#define MAP_H_

#include <list>
#include <string>
#include <vector>
#include "entity.h"

#define TILESIZE (0x1)

class CPlayer;

class CMap
{
   public:
      class ATile : public ABaseObject
      {
	 public:
	    enum  EType
	    {
	       EMPTY,
	       BREAKABLE_WALL,
	       UNBREAKABLE_WALL,
	       EXPLOSION_WALL,
	       PLAYER
	    };
	 public:
	    ATile(EType);
	    virtual ~ATile();

	    void addEntity(AEntity *);
	    void removeEntity(AEntity *);
	    void explodeEntity(AEntity *);

	    bool canPassThrough(CPlayer const*);
	    void getPowerups(CPlayer *);

	    EType       getType() const {return _type;}
	    void	setType(EType const& type) { _type = type;}
	    virtual bool hitByExplosion(AEntity *) = 0;
	    virtual void draw(gdl::AShader&) = 0;

	 private:
	    EType                _type;
	    std::list<AEntity*>  _entities;
      };
   public:
   CMap(int, int, int);
      CMap(std::string const&);
      ~CMap();

      int   size() const;
      bool  save() const;
      bool  load(std::string const&);
      void  destroyTile(int, int);
      void  createExplosionTile(int, int);
      bool  generate(int, int, std::string const& = "untitled");

      ATile *getTile(int x, int y) const;
      std::vector<ATile*>& operator[](int);

      void draw(gdl::AShader&);

 protected:
      bool	detectPlayer(int, int);
      void	destroyEverything(int, int);
   private:
      int                                 _maxPlayer;
      std::string                         _name;
      std::vector<std::vector<ATile*> >   _level;
};

#endif //MAP_H_
