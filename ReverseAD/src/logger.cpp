#include <iostream>
#include "reversead/logger.hpp"

namespace ReverseAD {

//Log log(&(std::cout));
Log log(nullptr, &(std::cerr), &(std::cerr));

} // namespace ReverseAD
