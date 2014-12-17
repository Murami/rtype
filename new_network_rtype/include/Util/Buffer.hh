#ifndef BUFFER_HH
# define BUFFER_HH

# include <deque>

namespace Util
{

  class Buffer
  {
  public:
    Buffer();
    ~Buffer();

    void	read(char *buffer, int size);
    void	write(const char *buffer, int size);
    void	pick(char *buffer, int size);
    void	consume(int size);
    int		size();

  private:
    std::deque<char> _buffer;
  };

} /* namespace Util */

#endif /* BUFFER_HH */
