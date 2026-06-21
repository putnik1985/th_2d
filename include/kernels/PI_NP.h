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

class PI_NP : public Kernel
{
public:
  PI_NP(const InputParameters & parameters);
  static InputParameters validParams();

protected:
  virtual Real computeQpResidual() override;
////////////////////////// virtual Real computeQpJacobian() override;

private:
  Real rw;
  Real ri;
  Real T0;
  Real Lf;

  const VariableValue& T;
  const VariableValue& pw;
};
