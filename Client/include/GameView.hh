
#ifndef _GAME_VIEW_HH_
# define _GAME_VIEW_HH_

# include <map>
# include <SFML/Graphics.hpp>
# include "GameObservable.hh"

class	IObject;

namespace	RType
{
  class	GameView : public GameObservable
  {
  public:
    GameView();
    ~GameView();

  public:
    void	run(sf::RenderWindow&);

  private:
    void	update();
    void	render(sf::RenderWindow&);

  private:
    std::map<int, IObject*>	_map;
    bool			_run;
  };
}

#endif
