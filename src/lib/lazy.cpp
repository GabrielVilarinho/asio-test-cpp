#include "lazy.h"

Lazy::Lazy(const int &milliseconds) {
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}