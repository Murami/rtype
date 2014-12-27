#include	<stdexcept>

#include	"RtypeClient.hh"

int		main()
{
    std::cout << "Sizeof State : " << sizeof(RtypeProtocol::State) << std::endl;
  std::cout << "id      " << offsetof (RtypeProtocol::State, id) << std::endl;
  std::cout << "state : " << offsetof (RtypeProtocol::State, state) << std::endl;
  RtypeClient	client;

  try
    {
      client.run();
    }
  catch (std::runtime_error e)
    {
      std::cerr << "\033[31mCaught exception when attempting to "
		<< e.what() << "\033[0m" << std::endl;
      return (-1);
    }
  return (0);
}
