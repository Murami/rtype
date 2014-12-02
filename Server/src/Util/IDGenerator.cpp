#include "Util/IDGenerator.hh"

namespace Util
{
  IDGenerator::IDGenerator() : _id(0)
  {
  }

  IDGenerator::~IDGenerator()
  {
  }

  void		IDGenerator::reset()
  {
    _id = 0;
  }

  unsigned int	IDGenerator::generate()
  {
    _id++;
    return (_id);
  }
};
