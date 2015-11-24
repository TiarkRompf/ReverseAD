#ifndef BASE_ACBaseIVE_H_
#define BASE_ACBaseIVE_H_

#include <math.h>
#include <iostream>
#include "reversead/common/reversead_base.hpp"
#include "reversead/common/opcodes.hpp"

//#define REVERSEAD_BASE_ACTIVE_DEBUG

#define REVERSE_AD_CPP11

#define REVERSE_AD_ONLY_REVERSE

namespace ReverseAD {

template <typename Base>
class BaseActive {
 public:

  #include "base_active_assign.ipp" // constructor and assignment
  #include "base_active_plus.ipp" // plus +
  #include "base_active_mult.ipp" // mult *
  #include "base_active_minus.ipp" // minus -
  #include "base_active_div.ipp" // div /
  #include "base_active_sincos.ipp" // sin cos

  inline Base getVal() {return val;}
  inline locint getLoc() {return loc;}
 private:
  Base val;
  locint loc;
};  

} // namespace ReverseAD

typedef ReverseAD::BaseActive<double> adouble;

#endif // BASE_ACTIVE_H_