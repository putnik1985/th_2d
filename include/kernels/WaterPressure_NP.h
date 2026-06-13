//* This file is part of the MOOSE framework
//* https://mooseframework.inl.gov
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#pragma once

#include "Kernel.h"

/**
 * Define the Kernel for a convection operator that looks like:
 *
 * (lambda grad(u),grad(test))
 *
 * where lambda is a given constant.
 */
class WaterPressure_NP : public Kernel
{
public:
  WaterPressure_NP(const InputParameters & parameters);
  Real conductivity(Real);
  static InputParameters validParams();

protected:
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;

private:
  Real k;
  Real kr;
  Real gammaw;
};
