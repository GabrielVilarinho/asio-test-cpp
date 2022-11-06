#include <thread>
#include <chrono>
class Lazy
{
public:
    ///Please do not use hardcoded delays in any project
    explicit Lazy(const int &milliseconds);
};