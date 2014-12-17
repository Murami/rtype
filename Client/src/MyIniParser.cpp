
#include <iostream>
#include "MyIniParser.hh"

MyIniParser::MyIniParser(std::string filename) : _file(filename.c_str(), std::ios::in)
{
  if (!_file)
    std::cerr << "the system cannot find the file " << filename << std::endl;
}

MyIniParser::~MyIniParser()
{
  if (_file)
    _file.close();
}

std::map<std::string, std::string>	MyIniParser::getEverythingInSection(std::string section)
{
  std::map<std::string, std::string>	res;
  char				tmp[128];
  std::string				copy;
  size_t				pos;
  std::string				key;
  std::string				value;

  if (!_file)
    return (res);

  _file.seekg(0);
  while (_file.getline(tmp, 128))
    {
      if (tmp[0] == '[')
	{
	  copy = tmp;
	  copy = copy.substr(0, copy.find("#"));
	  if ((pos = copy.find("]")) == std::string::npos)
	    continue;
	  if (copy.substr(1, pos - 1) == section)
	    break;
	}
    }
  while (_file.getline(tmp, 128))
    {
      if (tmp[0] == '[')
	break;
      copy = tmp;
      copy = copy.substr(0, copy.find("#"));
      if ((pos = copy.find("=")) == std::string::npos)
	continue;
      key = copy.substr(0, pos);
      value = copy.substr(pos + 1);
      value = value.substr(1, value.size() - 2);
      res[key] = value;
    }
  return (res);
}
