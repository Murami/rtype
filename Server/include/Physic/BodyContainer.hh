#ifndef PHYSIC_BODY_CONTAINER
#define PHYSIC_BODY_CONTAINER

namespace Physic
{
  class Body;

  class BodyContainer
  {
    friend class Body;

  protected:
    virtual void	add(Body& body) = 0;
    virtual void	remove(Body& body) = 0;
  };
};

#endif /* PHYSIC_BODY_CONTAINER */
