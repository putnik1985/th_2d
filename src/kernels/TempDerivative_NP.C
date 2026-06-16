#include "TempDerivative_NP.h"
#include <utility>

registerMooseObject("th_2DApp", TempDerivative_NP);

InputParameters
TempDerivative_NP::validParams()
{
  InputParameters params = TimeKernel::validParams();
  params.addRequiredParam<Real>("W", "temperature parameter");
  params.addRequiredParam<Real>("T0", "temperature offset");
  params.addRequiredParam<Real>("swres", "residual water saturation");
  params.addRequiredParam<Real>("ri", "ice density");
  params.addRequiredParam<Real>("rs", "soil density");
  params.addRequiredParam<Real>("rw", "water density");
  params.addRequiredParam<Real>("porosity", "porosity");
  params.addRequiredParam<Real>("Lf", "latent heat of fusion");
  params.addRequiredParam<Real>("ci", "ice specific heat capacity");
  params.addRequiredParam<Real>("cs", "soil specific heat capacity");
  params.addRequiredParam<Real>("cw", "water specific heat capacity");
  return params;
}

TempDerivative_NP::TempDerivative_NP(const InputParameters & parameters)
  : // You must call the constructor of the base class first
    TimeKernel(parameters),
    W(getParam<Real>("W")),
    T0(getParam<Real>("T0")),
    swres(getParam<Real>("swres")),
    ri(getParam<Real>("ri")),
    rs(getParam<Real>("rs")),
    rw(getParam<Real>("rw")),
    ci(getParam<Real>("ci")),
    cs(getParam<Real>("cs")),
    cw(getParam<Real>("cw")),
    porosity(getParam<Real>("porosity")),
    Lf(getParam<Real>("Lf"))
{
}

Real
TempDerivative_NP::computeQpResidual()
{
  Real sw;
  Real dsw_dT;

  Real T = _u[_qp];
  sw = saturation(T).first;
  dsw_dT = saturation(T).second;

  Real si = 1. - sw;
  Real ksi = porosity * ri / (sw + ri / rw * si);

  Real n = porosity;
  volume_heat_capacity = (1-n)*rs*cs + (n*sw)*rw*cw + (n*si)*ri*ci; 
  return (volume_heat_capacity + Lf * ksi * dsw_dT) * _u_dot[_qp] * _test[_i][_qp]; 
}

Real
TempDerivative_NP::computeQpJacobian()
{
  Real sw;
  Real dsw_dT;

  Real T = _u[_qp];
  sw = saturation(T).first;
  dsw_dT = saturation(T).second;

  Real si = 1. - sw;
  Real ksi = porosity * ri / (sw + ri / rw * si);

  Real n = porosity;
  volume_heat_capacity = (1-n)*rs*cs + (n*sw)*rw*cw + (n*si)*ri*ci; 
  return (volume_heat_capacity + Lf * ksi * dsw_dT) * _du_dot_du[_qp] * _phi[_j][_qp] * _test[_i][_qp]; 
}

std::pair<Real,Real> TempDerivative_NP::saturation(Real T){
     Real s, ds;
     std::pair<Real, Real> res;
     s = 0.;
    ds = 0.;
     s = (1.-swres) * exp(-(T-T0)*(T-T0)/(W*W)) + swres;
    ds = (1.-swres) * exp(-(T-T0)*(T-T0)/(W*W)) * (-2. * (T-T0)/(W*W));

     res = std::make_pair(s, ds);
     return res;
}
