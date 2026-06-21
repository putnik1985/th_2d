//* This file is part of the MOOSE framework
//* https://mooseframework.inl.gov
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "PI_NP.h"

registerMooseObject("th_2DApp", PI_NP);

InputParameters
PI_NP::validParams()
{
  InputParameters params = Kernel::validParams();
  params.addRequiredParam<Real>("rw","rw");
  params.addRequiredParam<Real>("ri","ri");
  params.addRequiredParam<Real>("T0","T0");
  params.addRequiredParam<Real>("Lf","Lf");

  params.addRequiredCoupledVar("pw","water pressure");
  params.addRequiredCoupledVar("T","temperature");
  return params;
}

PI_NP::PI_NP(const InputParameters & parameters)
  : // You must call the constructor of the base class first
    Kernel(parameters),
    rw(getParam<Real>("rw")),
    ri(getParam<Real>("ri")),
    T0(getParam<Real>("T0")),
    Lf(getParam<Real>("Lf")),

     T(coupledValue("T")),
    pw(coupledValue("pw"))
{
}

Real
PI_NP::computeQpResidual()
{
  return (pw[_qp] / rw - _u[_qp] / ri - Lf * log(T[_qp]/T0)) * _test[_i][_qp]; 
}

