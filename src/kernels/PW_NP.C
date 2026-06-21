//* This file is part of the MOOSE framework
//* https://mooseframework.inl.gov
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "PW_NP.h"

registerMooseObject("th_2DApp", PW_NP);

InputParameters
PW_NP::validParams()
{
  InputParameters params = Kernel::validParams();
  params.addRequiredParam<Real>("kappaw","kappaw");

  params.addRequiredCoupledVar("pi","ice pressure");
  params.addRequiredCoupledVar("p","pore pressure");
  return params;
}

PW_NP::PW_NP(const InputParameters & parameters)
  : // You must call the constructor of the base class first
    Kernel(parameters),
    kappaw(getParam<Real>("kappaw")),

     p(coupledValue("p")),
    pi(coupledValue("pi"))
{
}

Real
PW_NP::computeQpResidual()
{
  kappai = 1. - kappaw;
  return (p[_qp] - kappaw * _u[_qp] - kappai * pi[_qp]) * _test[_i][_qp]; 
}

