//* This file is part of the MOOSE framework
//* https://mooseframework.inl.gov
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "Mass_Balance_PW_T_NP.h"

registerMooseObject("th_2DApp", Mass_Balance_PW_T_NP);

InputParameters
Mass_Balance_PW_T_NP::validParams()
{
  InputParameters params = Kernel::validParams();
  params.addRequiredParam<Real>("rw","water density");
  params.addRequiredParam<Real>("ri","ice density");
  params.addRequiredParam<Real>("kr","relative permeability");
  params.addRequiredParam<Real>("k","permeability");
  params.addRequiredParam<Real>("gammaw","specific weight");
  params.addRequiredParam<Real>("T0","T0");
  params.addRequiredParam<Real>("swres","swres");
  params.addRequiredParam<Real>("W","W");
  params.addRequiredParam<Real>("n","n");
  params.addRequiredParam<Real>("Lf","Lf");
  params.addRequiredParam<Real>("kappaw","kappaw");
  params.addRequiredParam<Real>("bf","bf");

  params.addRequiredCoupledVar("T","temperature");
  return params;
}

Mass_Balance_PW_T_NP::Mass_Balance_PW_T_NP(const InputParameters & parameters)
  : // You must call the constructor of the base class first
    Kernel(parameters),
    rw(getParam<Real>("rw")),
    ri(getParam<Real>("ri")),
    kr(getParam<Real>("kr")),
     k(getParam<Real>("k")),
    gammaw(getParam<Real>("gammaw")),
    T0(getParam<Real>("T0")),
    swres(getParam<Real>("swres")),
    W(getParam<Real>("W")),
    n(getParam<Real>("n")),
    Lf(getParam<Real>("Lf")),
    kappaw(getParam<Real>("kappaw")),
    bf(getParam<Real>("bf")),
    dT_dt(coupledDot("T")),
    T(coupledValue("T"))
{
}

Real
Mass_Balance_PW_T_NP::computeQpResidual()
{
  Real sw = saturation(T[_qp]).first;
  Real dsw = saturation(T[_qp]).second;
  Real kappai = 1.0 - kappaw;

/**************************************
  std::cout << "dsw: " << dsw 
            << "rw: " << rw
            << "T: " << T[_qp]
            << "Lf: " << Lf 
            << "swres: " << swres 
            << "W: " << W 
            << std::endl;
**************************************/

  return  kr * k / gammaw * _grad_u[_qp] * _grad_test[_i][_qp] + 
          (n * (rw - ri) / rw * dsw - sw * n * bf * kappai * ri * Lf * 1.0 / T[_qp])* dT_dt[_qp] * _test[_i][_qp];
}

Real
Mass_Balance_PW_T_NP::computeQpJacobian()
{
  Real sw = saturation(T[_qp]).first;
  Real dsw = saturation(T[_qp]).second;
  Real kappai = 1.0 - kappaw;
  return  kr * k / gammaw * _grad_phi[_j][_qp] * _grad_test[_i][_qp]; 
}

std::pair<Real,Real>
Mass_Balance_PW_T_NP::saturation(Real T){
  Real sw = (1. - swres) * exp(-(T-T0)*(T-T0)/(W*W)) + swres;
  Real dsw = (1. - swres) * exp(-(T-T0)*(T-T0)/(W*W)) * (-2.) * (T-T0) / (W*W);
  return std::make_pair(sw, dsw);
}
