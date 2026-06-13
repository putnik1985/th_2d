#pragma once

#include "TimeKernel.h"

class PressureDerivative_NP : public TimeKernel
{
public:
  PressureDerivative_NP(const InputParameters & parameters);
  static InputParameters validParams();

protected:
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;

private:
  Real n;
  Real bf;
};

