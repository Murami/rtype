
#include <iostream>
#include "SoundManager.hh"
#include "MyIniParser.hh"

namespace	RType
{

  SoundManager::SoundManager()
  {
    
  }

  SoundManager::~SoundManager()
  {
    
  }

  std::map<std::string, std::shared_ptr<sf::SoundBuffer> >	SoundManager::initializeSounds()
  {
    MyIniParser							parse("sound.conf");
    std::map<std::string, std::string>				tmp = parse.getEverythingInSection("sounds");
    std::map<std::string, std::shared_ptr<sf::SoundBuffer> >	res;

    for (std::map<std::string, std::string>::iterator it = tmp.begin(); it != tmp.end(); it++)
      {
	auto sound = std::make_shared<sf::SoundBuffer> ();

	if (sound->loadFromFile(it->second.c_str()))
	  res[it->first] = sound;
      }

    return (res);
  }

  std::map<std::string, std::shared_ptr<sf::Music> >	SoundManager::initializeMusics()
  {
    MyIniParser						parse("sound.conf");
    std::map<std::string, std::string>			tmp = parse.getEverythingInSection("musics");
    std::map<std::string, std::shared_ptr<sf::Music> >	res;

    for (std::map<std::string, std::string>::iterator it = tmp.begin(); it != tmp.end(); it++)
      {
	auto	music = std::make_shared<sf::Music> ();

	if (music->openFromFile(it->second.c_str()))
	  res[it->first] = music;
      }
    return (res);
  }

  bool	SoundManager::Play(std::string name, bool loop)
  {
    if (_soundsMap.find(name) != _soundsMap.end())
      {
	std::shared_ptr<sf::Sound>	sound = std::make_shared<sf::Sound>();

	sound->setBuffer(*_soundsMap[name]);
    	sound->play();
	_trash.push_back(sound);
    	return (true);
      }

    if (_musicsMap.find(name) != _musicsMap.end())
      {
	_musicsMap[name]->setLoop(loop);
    	_musicsMap[name]->play();
    	return (true);
      }
    return (false);
  }

  bool	SoundManager::Pause(std::string name)
  {
    if (_musicsMap.find(name) != _musicsMap.end())
      {
	_musicsMap[name]->pause();
	return (true);
      }
    return (false);    
  }

  bool	SoundManager::Stop(std::string name)
  {
    if (_musicsMap.find(name) != _musicsMap.end())
      {
	_musicsMap[name]->stop();
	return (true);
      }
    return (false);
  }

  std::map<std::string, std::shared_ptr<sf::SoundBuffer> >	SoundManager::_soundsMap = SoundManager::initializeSounds();
  std::map<std::string, std::shared_ptr<sf::Music> >		SoundManager::_musicsMap = SoundManager::initializeMusics();
  std::list<std::shared_ptr<sf::Sound> >			SoundManager::_trash;
}
