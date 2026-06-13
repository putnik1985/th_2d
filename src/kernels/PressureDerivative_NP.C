#include "PressureDerivative_NP.h"
#include <utility>

registerMooseObject("th_2DApp", PressureDerivative_NP);

InputParameters
PressureDerivative_NP::validParams()
{
  InputParameters params = TimeKernel::validParams();
  params.addRequiredParam<Real>("n", "porosity");
  params.addRequiredParam<Real>("bf", "fluid compressibility");

  params.addRequiredCoupledVar("T","temperature");  
  return params;
}

PressureDerivative_NP::PressureDerivative_NP(const InputParameters & parameters)
  : // You must call the constructor of the base class first
    TimeKernel(parameters),
    n(getParam<Real>("n")),
    bf(getParam<Real>("bf"))
{
}

Real
PressureDerivative_NP::computeQpResidual()
{
  Real sw;
  Real dsw_dT;

  return n * bf  * _u_dot[_qp] * _test[_i][_qp]; 
}

Real
PressureDerivative_NP::computeQpJacobian()
{
  Real sw;
  Real dsw_dT;

  return n * bf  * _du_dot_du[_qp] * _phi[_j][_qp] * _test[_i][_qp]; 
}
