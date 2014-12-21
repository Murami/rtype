
#ifndef _GAME_VIEW_HH_
# define _GAME_VIEW_HH_

# include <map>
# include <SFML/Graphics.hpp>
# include "GameObservable.hh"
# include "ScrollingBackground.hh"
# include "RtypeProtocol.hh"

namespace	Util
{
  class		Mutex;
}

class	IObject;

class	GameView : public GameObservable
{
public:
  GameView();
  ~GameView();

public:
  void	run(sf::RenderWindow&, Util::Mutex*);
  void	add(int id, IObject*);
  void	erase(int id);

public:
  void	updateById(int id, RtypeProtocol::Position pos);

private:
  void	update();
  void	render(sf::RenderWindow&);

private:
  std::vector<ScrollingBackground*>	_backgroundVector;
  std::map<int, IObject*>		_objectMap;
  bool					_run;
};

#endif
