#include	<stdexcept>
#include	<iostream>
#include	"ConfigurationParser.hh"

ConfigurationParser::ConfigurationParser()
{
}

const std::string	ConfigurationParser::_getSectionName(const std::string &line)
{
  std::string		name;

  for (std::size_t i = 0; i < line.size() && line[i] != ']'; i++)
    name += line[i];
  return (name);
}

bool			ConfigurationParser::_parseData(const std::string& line)
{
  std::string		dataName;
  std::string		data;
  std::size_t		i;

  for (i = 0; i < line.size() && line[i] != '='; i++)
    dataName += line[i];
  if (i == line.size())
    return (false);
  i++;
  for (; i < line.size(); i++)
    data += line[i];
  _datas[dataName] = data;
  return (true);
}

bool			ConfigurationParser::parse(const std::string& filename)
{
  std::ifstream		ifstr;
  std::string		sectionName;
  char			buff[256];

  ifstr.open(filename);
  if (!ifstr.is_open())
    {
      std::cerr << "Error : '" << filename << "' could not open file." << std::endl;
      return (false);
    }
  while (ifstr.getline(&buff[0], 256))
    {
      if (buff[0] == '[')
	sectionName = _getSectionName(std::string(&buff[1]));
      else if (buff[0] != '#')
	_parseData(buff);
    }
  return (true);
}

const std::string&	ConfigurationParser::getValueByName(const std::string& value)
{
  std::map<std::string, std::string>::key_compare comp = _datas.key_comp();
  for (std::map<std::string, std::string>::iterator it = _datas.begin();
       it != _datas.end(); it++)
    {
      if (it->first == value)
	return (it->second);
    }
  throw (std::runtime_error(value + std::string(" is not contained in datas")));
}

ConfigurationParser::~ConfigurationParser()
{
}
