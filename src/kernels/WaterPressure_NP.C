//* This file is part of the MOOSE framework
//* https://mooseframework.inl.gov
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "WaterPressure_NP.h"

/**
 * All MOOSE based object classes you create must be registered using this macro.  The first
 * argument is the name of the App you entered in when running the stork.sh script with an "App"
 * suffix. If you ran "stork.sh Example", then the argument here becomes "ExampleApp". The second
 * argument is the name of the C++ class you created.
 */
registerMooseObject("th_2DApp", WaterPressure_NP);

/**
 * This function defines the valid parameters for
 * this Kernel and their default values
 */
InputParameters
WaterPressure_NP::validParams()
{
  InputParameters params = Kernel::validParams();
  params.addRequiredParam<Real>("k", "permeability");
  params.addRequiredParam<Real>("kr", "relative permeability");
  params.addRequiredParam<Real>("gammaw", "specific water weight");
  return params;
}

WaterPressure_NP::WaterPressure_NP(const InputParameters & parameters)
  : // You must call the constructor of the base class first
    Kernel(parameters),
    k(getParam<Real>("k")),
    kr(getParam<Real>("kr")),
    gammaw(getParam<Real>("gammaw"))
{
}

Real
WaterPressure_NP::computeQpResidual()
{
  Real lambda = kr * k / gammaw;
  return _grad_test[_i][_qp] * (lambda * _grad_u[_qp]);
}

Real
WaterPressure_NP::computeQpJacobian()
{
  Real lambda = kr * k / gammaw;
  return _grad_test[_i][_qp] * (lambda * _grad_phi[_j][_qp]);
}
