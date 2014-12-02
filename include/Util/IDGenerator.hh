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
    ~IDGenerator();

    void		reset();
    unsigned int	generate();
  };
};

#endif /* UTIL_IDGENERATOR */
