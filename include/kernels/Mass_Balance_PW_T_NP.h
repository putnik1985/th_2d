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

class Mass_Balance_PW_T_NP : public Kernel
{
public:
  std::pair<Real,Real>  saturation(Real);
  Mass_Balance_PW_T_NP(const InputParameters & parameters);
  static InputParameters validParams();

protected:
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;

private:
  Real rw;
  Real ri;
  Real kr;
  Real k;
  Real gammaw;
  Real T0;
  Real W;
  Real swres;
  Real n;
  Real bf;
  Real kappaw;
  Real Lf;

  const VariableValue& dT_dt;
  const VariableValue& T;
};
