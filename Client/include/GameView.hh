
#ifndef _GAME_VIEW_HH_
# define _GAME_VIEW_HH_

# include <map>
# include <SFML/Graphics.hpp>
# include "GameObservable.hh"
# include "ScrollingBackground.hh"
# include "RtypeProtocol.hh"
# include "Mutex.hh"
# include "Life.hh"
# include "Wall.hh"

class	IObject;

class	GameView : public GameObservable
{
public:
  GameView();
  ~GameView();

public:
  void	run(sf::RenderWindow&, Util::Mutex*);
  void	stop();
  void	emptyMap();

  void	setGameRunning(bool);
  void	add(int id, IObject*);
  void	erase(int id);
  void	updateLife(int life);
  void	isGameEnd(bool);
  void	isGameIsWin(bool);

public:
  bool	updateById(int id, RtypeProtocol::Position pos);

private:
  void	update(float);
  void	render(sf::RenderWindow&);

private:
  std::vector<ScrollingBackground*>	_backgroundVector;
  std::map<int, IObject*>		_objectMap;
  bool					_run;
  Life					_life;
  Wall					_wall;
  bool					_gameEnd;
  bool					_gameWin;
  sf::Texture				_texture;
  sf::Sprite				_sprite;
};

#endif

