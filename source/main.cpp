#include <iostream>
#include <time.h>
#include "asset.h"
#include "gameengine.h"

int	main(int ac, char *av[])
{
  srand(time(NULL));

  CAsset      asset;
  CGameEngine engine;
  std::string bot;
  std::string map;

  bot = "-b";
  map = "-m";
  if (ac != 1)
    {
      if (ac > 2)
	{
	  for (int i = 0; av[i]; ++i)
	    {
	      if (bot.compare(av[i]) == 0 && av[i + 1] != NULL)
		{
		  if (atoi(av[i + 1]) <= 25 && atoi(av[i + 1]) >= 0)
		    CGameEngine::_nbAI = atoi(av[i + 1]);
		  else
		    {
		      std::cout << "Invalid bot number" << std::endl;
		      return (0);
		    }
		}
	      else if (map.compare(av[i]) == 0 && av[i + 1] != NULL && av[i + 2] != NULL)
		{
		  if (((atoi(av[i + 1]) >= 25 && atoi(av[i + 2]) >= 25)) && (atoi(av[i + 1]) <= 150 && atoi(av[i + 2]) <= 150))
		    CGameEngine::_mapSize = glm::vec2(atoi(av[i + 1]), atoi(av[i + 2]));
		  else
		    {
		      std::cout << "Invalid map size"  << std::endl;
		      return (0);
		    }
		}
	    }
	}
      else
	{
	  std::cout << "Usage: ./Bomberman [-b nb] [-m size.x size.y]" << std::endl;
	  return (0);
	}
    }

  if (!engine.init())
    return EXIT_FAILURE;

  if (!asset.loadAll())
    return EXIT_FAILURE;

  engine.loop();
  return EXIT_SUCCESS;
}
