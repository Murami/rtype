
#ifndef _PLUGIN_LOADER_HPP_
# define _PLUGIN_LOADER_HPP_

# include <list>
# include <string>
# include <map>
# include <algorithm>
# include "IDynamicFile.hh"
# include "IDirent.hh"

template <typename T>
class	PluginLoader
{
public:
  PluginLoader(std::string directory) : _pathDirectory(directory)
  {
    Dirent::IDirent			*dir = Dirent::create(directory);
    std::list<std::string>		fileList;
    std::list<std::string>::iterator	it;
    DynamicFile::IDynamicFile		*tmp;
    std::string			(*hook)();

#if defined (__unix__)
    fileList = dir->getFilesNameByExtension("so");
#elif defined (WIN32) || defined (_WIN32)
    fileList = dir->getFilesNameByExtension("dll");
#endif
    for (it = fileList.begin(); it != fileList.end(); it++)
      {
	tmp = DynamicFile::create(_pathDirectory + Dirent::separator + *it);
	hook = reinterpret_cast<std::string (*)()>(tmp->loadSymbol("get_monster_name"));
	_filenameList.push_back(*it);
	_pluginsMap[hook()] = tmp;
	_fileAndPluginName[*it] = hook();
      }
    delete (dir);
  }

  ~PluginLoader()
  {
    std::map<std::string, DynamicFile::IDynamicFile*>::iterator	it;

    for (it = _pluginsMap.begin(); it != _pluginsMap.end(); it++)
      delete (it->second);
  }

  void	refresh()
  {
    Dirent::IDirent			*dir = Dirent::create(_pathDirectory);
    std::list<std::string>		fileList;
    std::list<std::string>::iterator	it;
    DynamicFile::IDynamicFile		*tmp;
    std::string			(*hook)();
    std::list<std::string>		copy;

#if defined (__unix__)
    fileList = dir->getFilesNameByExtension("so");
#elif defined (WIN32) || defined (_WIN32)
    fileList = dir->getFilesNameByExtension("dll");
#endif
    /* je rajoute les nouveaux fichiers */
    for (it = fileList.begin(); it != fileList.end(); it++)
      {
	if (std::find(_filenameList.begin(), _filenameList.end(), *it) == _filenameList.end())
	  {
	    tmp = DynamicFile::create(_pathDirectory + Dirent::separator + *it);
	    hook = reinterpret_cast<std::string (*)()>(tmp->loadSymbol("get_monster_name"));
	    _filenameList.push_back(*it);
	    _pluginsMap[hook()] = tmp;
	    _fileAndPluginName[*it] = hook();
	  }
      }
      
    /* j'enlève les fichiers obsolètes */
    copy = _filenameList;
    for (it = copy.begin(); it != copy.end(); it++)
      {
	if (std::find(fileList.begin(), fileList.end(), *it) == fileList.end())
	  {
	    _filenameList.remove(*it);
	    delete (_pluginsMap[_fileAndPluginName[*it]]);
	    _pluginsMap.erase(_fileAndPluginName[*it]);
	    _fileAndPluginName.erase(*it);
	  }
      }
    delete (dir);
  }

  std::list<std::string>	getPluginList()
  {
    std::list<std::string>						ret;
    std::map<std::string, DynamicFile::IDynamicFile*>::iterator	it;

    for (it = _pluginsMap.begin(); it != _pluginsMap.end(); it++)
      ret.push_back(it->first);
    return (ret);
  }

  T		*load(const std::string& name)
  {
    T		*(*res)();

    if (_pluginsMap.find(name) == _pluginsMap.end())
      throw (std::runtime_error("Unknown symbol " + name));

    try
      {
	res = reinterpret_cast<T* (*)()>(_pluginsMap[name]->loadSymbol("instantiate_plugin"));
      }
    catch (const std::exception& e)
      {
	throw (e);
      }
    return (res());
  }

  void	unload(const std::string& name)
  {
    delete (_pluginsMap[name]);
    _pluginsMap.erase(name);
    _fileAndPluginName.erase(name);
  }

private:
  const std::string					_pathDirectory;
  std::list<std::string>				_filenameList;
  std::map<std::string, DynamicFile::IDynamicFile*>	_pluginsMap;
  std::map<std::string, std::string>			_fileAndPluginName;
};

#endif /* _PLUGIN_LOADER_HPP_ */
