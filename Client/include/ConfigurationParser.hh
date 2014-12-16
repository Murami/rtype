#ifndef		__CONFIGURATIONPARSER_HH__
# define	__CONFIGURATIONPARSER_HH__

# include	<fstream>
# include	<map>

class		ConfigurationParser
{
private:
  std::map<std::string, std::string>	_datas;

private:
  const std::string	_getSectionName(const std::string&);
  bool			_parseData(const std::string&);

public:
  ConfigurationParser();
  ~ConfigurationParser();

public:
  const std::string&	getValueByName(const std::string& value);
  bool			parse(const std::string& filename);

};

#endif
