#include <iostream>

#include "reversead/reversead.hpp"

using ReverseAD::locint;

double myEps = 1.E-10;

void check_answer(ReverseAD::TrivialTrace<double>* trace,
                  bool& done,
                  double vx) {
      double vy;
      ReverseAD::TrivialTrace<double>* new_trace =
        ReverseAD::BaseFunctionReplay::replay_ind(trace, &vy,1, &vx, 1);
      if (fabs(vy - vx*vx) > myEps) {
        done = true;
      }
      ReverseAD::BaseReverseHessian<double> hessian(new_trace);
      hessian.compute(1,1);
      double** adjoints;
      hessian.retrieve_adjoint(&adjoints);
      if (fabs(adjoints[0][0]-2*vx) > myEps) {
        done = true;
      }
      int *size;
      locint **rind;
      locint **cind;
      double** values;
      hessian.retrieve_hessian_sparse_format(&size, &rind, &cind, &values);
      if (size[0] == 1) {
        if (fabs(values[0][0]-2.0) > myEps) {
          done = true;
        }
      } else {
        done = true;
      }
      if (done) {
        std::cout << "y = " << vy << std::endl;
        std::cout << "A[0] = " << adjoints[0][0] << std::endl;
        std::cout << "H[0] = " << values[0][0] << std::endl;
      }
}
int main() {
  bool done = false;
  int testCase = 0;
  const char* testLine;
  while(!done) {
    adouble x, y;
    ReverseAD::trace_on<double>();
    x <<= 2.0;
    switch(testCase) {
    case 0:
      y = x*x;
      testLine = "y=x*x";
      break;
    case 1:
      y = (x*x*x)/x;
      testLine = "y=(x*x*x)/x";
      break;
    case 2:
      y = (x+2)*(x-2)+4;
      testLine = "(x+2)*(x-2)+4";
      break;
    case 3:
      y = sqrt(x*x)*x;
      testLine = "y=sqrt(x*x)*x";
      break;
    case 4:
      y = (2*x) / (2/x);
      testLine = "y=(2*x)/(2/x)";
      break;
    case 5:
      y = tan(atan(x*x/20))*20;
      testLine = "y=tan(atan(x*x/20))*20";
      break;
    case 6:
      y = exp(2*log(x));
      testLine = "y=exp(2*log(x))";
      break;
    case 7:
      y = sqrt(log(exp(x*x*x*x)));
      testLine = "y=sqrt(log(exp(x*x*x*x)))";
      break;
    case 8:
      y = pow(sqrt(x), 4);
      testLine = "y=pow(sqrt(x), 4)";
      break;
    case 9:
      y = pow(1,x)*x*sqrt(pow(x,2));
      testLine = "y=pow(1,x)*x*sqrt(pow(x,2))";
      break;
    case 10:
      y = 0;
      x += 2;
      y += x*x;
      y -=4;
      y -= 4*x;
      y += 8;
      testLine = "y=0;x+=2;y+=x*x;y-=4;y-=4*x;y+=8;";
      break;
    case 11:
      y = x;
      y *= x*x;
      y *= 2;
      y /= x;
      y /= 2;
      testLine = "y=x;y*=x*x;y*=2;y/=x;y/=2";
      break;
    default:
      done = true;
      break;
    }
    double vy;
    y >>= vy;
    if (!done) {
      ReverseAD::TrivialTrace<double>* trace = ReverseAD::trace_off<double>();
      check_answer(trace, done, 1.0);
      check_answer(trace, done, 2.0);
      check_answer(trace, done, 3.0);
      if (done) {
        std::cout << "test " << testLine << " fail!" << std::endl;
        exit(-1);
      }
      std::cout << "test " << testLine  << " ok." << std::endl;
    }
    testCase++;
  }
}
