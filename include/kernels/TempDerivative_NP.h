#pragma once

#include "TimeKernel.h"

class TempDerivative_NP : public TimeKernel
{
public:
  TempDerivative_NP(const InputParameters & parameters);
  static InputParameters validParams();
  std::pair<Real, Real> saturation(Real);

protected:
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;

private:
  Real volume_heat_capacity;
  Real porosity;
  Real Lf;
  Real cs;
  Real cw;
  Real ci;
  Real rw;
  Real rs;
  Real ri;
  Real swres;
  Real W;
  Real T0;
};

