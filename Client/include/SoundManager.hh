
#ifndef _SOUND_MANAGER_HH_
# define _SOUND_MANAGER_HH_

# include <map>
# include <string>
# include <memory>
# include <list>
# include <SFML/Audio.hpp>

namespace	RType
{
  class	SoundManager
  {
  public:
    SoundManager();
    ~SoundManager();

    static bool	Play(std::string, bool loop = false);
    static bool Pause(std::string);
    static bool	Stop(std::string);

  private:
    static std::map<std::string, std::shared_ptr<sf::SoundBuffer> >	initializeSounds();
    static std::map<std::string, std::shared_ptr<sf::Music> >	initializeMusics();

    static std::map<std::string, std::shared_ptr<sf::SoundBuffer> >	_soundsMap;
    static std::map<std::string, std::shared_ptr<sf::Music> >		_musicsMap;
    static std::list<std::shared_ptr<sf::Sound> >			_trash;
  };
}

#endif
