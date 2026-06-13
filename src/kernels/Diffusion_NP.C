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
  params.addRequiredParam<Real>("lambda_unfrozen", "input paramter for the diffusion: thermal conductivity of soil");
  params.addRequiredParam<Real>("lambda_frozen", "input paramter for the diffusion: thermal conductivity of water");
  params.addRequiredParam<Real>("T0", "input paramter for the diffusion: onset on freezing temperature");
  params.addRequiredParam<Real>("Tf", "input paramter for the diffusion: full freezing temperature");
  return params;
}

Diffusion_NP::Diffusion_NP(const InputParameters & parameters)
  : // You must call the constructor of the base class first
    Kernel(parameters),
    _lambda_unfrozen(getParam<Real>("lambda_unfrozen")),
    _lambda_frozen(getParam<Real>("lambda_frozen")),
    _T0(getParam<Real>("T0")),
    _Tf(getParam<Real>("Tf"))
{
}

Real
Diffusion_NP::computeQpResidual()
{
  Real T = _u[_qp];
  Real lambda = conductivity(T);
  return _grad_test[_i][_qp] * (lambda * _grad_u[_qp]);
}

Real
Diffusion_NP::computeQpJacobian()
{
  Real T = _u[_qp];
  Real lambda = conductivity(T);
  return _grad_test[_i][_qp] * (lambda * _grad_phi[_j][_qp]);
}

Real
Diffusion_NP::conductivity(Real T){
  Real lambda; 
  if (T<_Tf) {
            return _lambda_frozen;
  } else if (T>_T0) {
            return _lambda_unfrozen;
  } else {
            return (T - _Tf)/(_T0 - _Tf) * _lambda_unfrozen + (1. - (T - _Tf)/(_T0 - _Tf)) * _lambda_frozen; 
  }
}
