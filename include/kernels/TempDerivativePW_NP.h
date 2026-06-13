#pragma once

#include "TimeKernel.h"

class TempDerivativePW_NP : public TimeKernel
{
public:
  TempDerivativePW_NP(const InputParameters & parameters);
  static InputParameters validParams();
  std::pair<Real, Real> saturation(Real);

protected:
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;

private:
  Real n;
  Real rw;
  Real rs;
  Real ri;
  Real swres;
  Real T0;
  Real W;
};

