#ifndef UTIL_IDGENERATOR
#define UTIL_IDGENERATOR

namespace Util
{
  class IDGenerator
  {
  private:
    unsigned int	_id;

  public:
    IDGenerator();
    IDGenerator(const IDGenerator& generator);
    ~IDGenerator();

    IDGenerator&	operator=(const IDGenerator& generator);

    void		reset();
    unsigned int	generate();
  };
};

#endif /* UTIL_IDGENERATOR */
