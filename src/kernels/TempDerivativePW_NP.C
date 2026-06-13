#include "TempDerivativePW_NP.h"
#include <utility>

registerMooseObject("th_2DApp", TempDerivativePW_NP);

InputParameters
TempDerivativePW_NP::validParams()
{
  InputParameters params = TimeKernel::validParams();
  params.addRequiredParam<Real>("swres", "residual water saturation");
  params.addRequiredParam<Real>("ri", "ice density");
  params.addRequiredParam<Real>("rs", "soil density");
  params.addRequiredParam<Real>("rw", "water density");
  params.addRequiredParam<Real>("n", "porosity");
  params.addRequiredParam<Real>("T0", "T0");
  params.addRequiredParam<Real>("W", "W");
  return params;
}

TempDerivativePW_NP::TempDerivativePW_NP(const InputParameters & parameters)
  : // You must call the constructor of the base class first
    TimeKernel(parameters),
    swres(getParam<Real>("swres")),
    ri(getParam<Real>("ri")),
    rs(getParam<Real>("rs")),
    rw(getParam<Real>("rw")),
    n(getParam<Real>("n")),
    T0(getParam<Real>("T0")),
    W(getParam<Real>("W"))
{
}

Real
TempDerivativePW_NP::computeQpResidual()
{
  Real sw;
  Real dsw_dT;

  Real T = _u[_qp];
  sw = saturation(T).first;
  dsw_dT = saturation(T).second;
  return (n * (rw - ri) / rw * dsw_dT) * _u_dot[_qp] * _test[_i][_qp]; 
}

Real
TempDerivativePW_NP::computeQpJacobian()
{
  Real sw;
  Real dsw_dT;

  Real T = _u[_qp];
  sw = saturation(T).first;
  dsw_dT = saturation(T).second;
  return (n * (rw - ri) / rw * dsw_dT) * _du_dot_du[_qp] * _phi[_j][_qp] * _test[_i][_qp]; 
}

std::pair<Real,Real> TempDerivativePW_NP::saturation(Real T){
     Real s, ds;
     std::pair<Real, Real> res;

     s = (1.-swres) * exp(-(T-T0)*(T-T0)/(W*W)) + swres;
    ds = (1.-swres) * exp(-(T-T0)*(T-T0)/(W*W)) * (-2. * (T-T0)/(W*W));

     res = std::make_pair(s, ds);
     return res;
}
