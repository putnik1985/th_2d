//* This file is part of the MOOSE framework
//* https://mooseframework.inl.gov
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "Convection_NP.h"

registerMooseObject("th_2DApp", Convection_NP);

InputParameters
Convection_NP::validParams()
{
  InputParameters params = Kernel::validParams();
  params.addRequiredParam<Real>("cw", "specific water heat conductivity");
  params.addRequiredParam<Real>("ci", "specific ice heat conductivity");
  params.addRequiredParam<Real>("rw", "water density");
  params.addRequiredParam<Real>("ri", "ice density");
  params.addRequiredParam<Real>("kr", "relative permeability");
  params.addRequiredParam<Real>("k",  "permeability");
  params.addRequiredParam<Real>("gammaw",  "specific weight");
  params.addRequiredParam<Real>("T0",  "T0");
  params.addRequiredParam<Real>("swres",  "swres");
  params.addRequiredParam<Real>("W",  "W");

  params.addRequiredCoupledVar("pw", "water pressure");
  return params;
}

Convection_NP::Convection_NP(const InputParameters & parameters)
  : // You must call the constructor of the base class first
    Kernel(parameters),
    cw(getParam<Real>("cw")),
    ci(getParam<Real>("ci")),
    rw(getParam<Real>("rw")),
    ri(getParam<Real>("ri")),
    kr(getParam<Real>("kr")),
     k(getParam<Real>("k")),
    gammaw(getParam<Real>("gammaw")),
    grad_pw(coupledGradient("pw"))
{
}

Real
Convection_NP::computeQpResidual()
{
  Real T = _u[_qp];
  Real sw = saturation(T);
  Real si = 1. - sw;
  Real theta = si / sw;

  Real a = (cw * rw + theta * ci * ri) * kr * k / gammaw;  
  return a * grad_pw[_qp] * _grad_u[_qp] * _test[_i][_qp];
}

Real
Convection_NP::computeQpJacobian()
{  
  Real T = _u[_qp];
  Real sw = saturation(T);
  Real si = 1. - sw;
  Real theta = si / sw;

  Real a = (cw * rw + theta * ci * ri) * kr * k / gammaw;  
  return a * grad_pw[_qp] * _grad_phi[_j][_qp] * _test[_i][_qp];
}

Real
Convection_NP::saturation(Real T){
  return (1. - swres) * exp(-(T-T0)*(T-T0)/(W*W)) + swres;
}
