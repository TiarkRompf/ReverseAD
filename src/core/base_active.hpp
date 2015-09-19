#ifndef BASE_ACBaseIVE_H_
#define BASE_ACBaseIVE_H_

#include <iostream>
#include "reversead.hpp"
#include "opcodes.hpp"

#define REVERSE_AD_CPP11

#define REVERSE_AD_ONLY_REVERSE

namespace ReverseAD {

template <typename Base>
class BaseActive {
 public:
  #include "base_active_assign.ipp" // constructor and assignment
  #include "base_active_plus.ipp" // plus +
  #include "base_active_mult.ipp" // mult *
  
  inline Base getVal() { return val;}
 private:
  Base val;
  locint loc;
};  

} // namespace ReverseAD

typedef ReverseAD::BaseActive<double> adouble;

#endif // BASE_ACTIVE_H_