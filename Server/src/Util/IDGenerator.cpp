#include "Util/IDGenerator.hh"

namespace Util
{
  IDGenerator::IDGenerator() : _id(0)
  {
  }

  IDGenerator::IDGenerator(const IDGenerator& generator)
  {
    _id = generator._id;
  }

  IDGenerator::~IDGenerator()
  {
  }

  IDGenerator&	IDGenerator::operator=(const IDGenerator&  generator)
  {
    _id = generator._id;

    return (*this);
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
