
#ifndef _MY_INI_PARSER_HH_
# define _MY_INI_PARSER_HH_

# include <map>
# include <string>
# include <fstream>

namespace	RType
{
  class	MyIniParser
  {
  public:
    MyIniParser(std::string filename);
    ~MyIniParser();

    std::map<std::string, std::string>	getEverythingInSection(std::string);
    

  private:
    std::ifstream	_file;
  };
}

#endif /* _MY_INI_PARSER_HH_ */
