#include "PressureDerivative_NP.h"
#include <utility>

registerMooseObject("th_2DApp", PressureDerivative_NP);

InputParameters
PressureDerivative_NP::validParams()
{
  InputParameters params = TimeKernel::validParams();
  params.addRequiredParam<Real>("n", "porosity");
  params.addRequiredParam<Real>("bf", "fluid compressibility");
  params.addRequiredParam<Real>("W", "W");
  params.addRequiredParam<Real>("T0", "T0");
  params.addRequiredParam<Real>("swres","swres");

  params.addRequiredCoupledVar("coupled","temperature");  
  return params;
}

PressureDerivative_NP::PressureDerivative_NP(const InputParameters & parameters)
  : // You must call the constructor of the base class first
    TimeKernel(parameters),
    n(getParam<Real>("n")),
    bf(getParam<Real>("bf")),
    T0(getParam<Real>("T0")),
     W(getParam<Real>("W")),
    swres(getParam<Real>("swres")),

     T(coupledValue("coupled"))
{
}

Real
PressureDerivative_NP::computeQpResidual()
{
  Real sw = saturation(T[_qp]);
  Real dsw_dT;
  //std::cout << "T: " << T[_qp] << std::endl;
  return sw * n * bf  * _u_dot[_qp] * _test[_i][_qp]; 
}

Real
PressureDerivative_NP::computeQpJacobian()
{
  Real sw = saturation(T[_qp]);
  Real dsw_dT;

  return sw * n * bf  * _du_dot_du[_qp] * _phi[_j][_qp] * _test[_i][_qp]; 
}

Real
PressureDerivative_NP::saturation(Real T){
  return (1. - swres) * exp(-(T-T0)*(T-T0)/(W*W)) + swres;
}
