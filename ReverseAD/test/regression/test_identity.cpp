#include <iostream>

#include "reversead/reversead.hpp"

using ReverseAD::locint;

double myEps = 1.E-10;

void check_answer(ReverseAD::TrivialTrace<double>* trace,
                  bool& done) {
      ReverseAD::BaseReverseHessian<double> hessian(trace);
      hessian.compute(1,1);
      double** adjoints;
      hessian.retrieve_adjoint(&adjoints);
      if (fabs(adjoints[0][0]-1.0) > myEps) {
        done = true;
      }
      int *size;
      locint **rind;
      locint **cind;
      double** values;
      hessian.retrieve_hessian_sparse_format(&size, &rind, &cind, &values);
      if (size[0] > 1) {
        done = true;
      } else if (size[0] == 1) {
        if (fabs(values[0][0]-0.0) > myEps) {
          done = true;
        }
      }
      if (done) {
        std::cout << "A[0] = " << adjoints[0][0] << std::endl;
        std::cout << "H[0] = " << values[0][0] << std::endl;
      }
}
int main() {
  bool done = false;
  int testCase = 0;
  const char* testLine;
  while(!done) {
    double vx = 2.0;
    adouble x, y;
    ReverseAD::trace_on<double>();
    x <<= vx;
    switch(testCase) {
    case 0:
      y = x;
      testLine = "y=x";
      break;
    case 1:
      y = x+x-x;
      testLine = "y=x+x-x";
      break;
    case 2:
      y = -2+(2+((x+2)-2));
      testLine = "-2+(2+((x+2)-2))";
      break;
    case 3:
      y = (2*x)/2;
      testLine = "y=(2*x)/2";
      break;
    case 4:
      y = (x*x)/x;
      testLine = "y=(x*x)/x";
      break;
    case 5:
      y = sqrt(x*x);
      testLine = "y=sqrt(x*x)";
      break;
    case 6:
      y = (2/x)*x*(x*0.5);
      testLine = "y=(2/x)*x*(x*0.5)";
      break;
    default:
      done = true;
      break;
    }
    double vy;
    y >>= vy;
    if (!done) {
      ReverseAD::TrivialTrace<double>* trace = ReverseAD::trace_off<double>();
      check_answer(trace, done);
      vx = 4;
      ReverseAD::TrivialTrace<double>* new_trace =
        ReverseAD::BaseFunctionReplay::replay_ind<double>(trace, &vy, 1, &vx, 1);
      if (vy != vx) {done = true;}
      check_answer(trace, done);
      check_answer(new_trace, done);
      if (done) {
        std::cout << "test " << testLine << " fail!" << std::endl;
        exit(-1);
      }
      std::cout << "test " << testLine  << " ok." << std::endl;
    }
    testCase++;
  }
}