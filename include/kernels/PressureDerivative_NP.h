#pragma once

#include "TimeKernel.h"

class PressureDerivative_NP : public TimeKernel
{
public:
  PressureDerivative_NP(const InputParameters & parameters);
  static InputParameters validParams();
  Real saturation(Real);

protected:
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;

private:
  Real n;
  Real bf;
  Real W;
  Real T0;
  Real swres;

  const VariableValue& T;
};

