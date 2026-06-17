//* This file is part of the MOOSE framework
//* https://mooseframework.inl.gov
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "Diffusion_NP.h"

/**
 * All MOOSE based object classes you create must be registered using this macro.  The first
 * argument is the name of the App you entered in when running the stork.sh script with an "App"
 * suffix. If you ran "stork.sh Example", then the argument here becomes "ExampleApp". The second
 * argument is the name of the C++ class you created.
 */
registerMooseObject("th_2DApp", Diffusion_NP);

/**
 * This function defines the valid parameters for
 * this Kernel and their default values
 */
InputParameters
Diffusion_NP::validParams()
{
  InputParameters params = Kernel::validParams();
  params.addRequiredParam<Real>("lambdas", "thermal conductivity of soil");
  params.addRequiredParam<Real>("lambdaw", "thermal conductivity of water");
  params.addRequiredParam<Real>("lambdai", "thermal conductivity of ice");
  params.addRequiredParam<Real>("T0", "input paramter for the diffusion: onset on freezing temperature");
  params.addRequiredParam<Real>("W", "W");
  params.addRequiredParam<Real>("n", "n");
  return params;
}

Diffusion_NP::Diffusion_NP(const InputParameters & parameters)
  : // You must call the constructor of the base class first
    Kernel(parameters),
    lambdas(getParam<Real>("lambdas")),
    lambdaw(getParam<Real>("lambdaw")),
    lambdai(getParam<Real>("lambdai")),
    T0(getParam<Real>("T0")),
    n(getParam<Real>("n")),
    W(getParam<Real>("W"))
{
}

Real
Diffusion_NP::computeQpResidual()
{
  Real T = _u[_qp];
  Real sw = saturation(T);
  Real si = 1. - sw;
  Real lambda = (1.-n)*lambdas + (n*sw)*lambdaw + (n*si)*lambdai;
  return _grad_test[_i][_qp] * (lambda * _grad_u[_qp]);
}

Real
Diffusion_NP::computeQpJacobian()
{
  Real T = _u[_qp];
  Real sw = saturation(T);
  Real si = 1. - sw;
  Real lambda = (1.-n)*lambdas + (n*sw)*lambdaw + (n*si)*lambdai;
  return _grad_test[_i][_qp] * (lambda * _grad_phi[_j][_qp]);
}

Real
Diffusion_NP::saturation(Real T){
  return (1.- swres) * exp(-(T-T0)*(T-T0)/(W*W)) + swres;
}
