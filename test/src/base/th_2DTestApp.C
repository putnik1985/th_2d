//* This file is part of the MOOSE framework
//* https://mooseframework.inl.gov
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html
#include "th_2DTestApp.h"
#include "th_2DApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "MooseSyntax.h"

InputParameters
th_2DTestApp::validParams()
{
  InputParameters params = th_2DApp::validParams();
  params.set<bool>("use_legacy_material_output") = false;
  params.set<bool>("use_legacy_initial_residual_evaluation_behavior") = false;
  return params;
}

th_2DTestApp::th_2DTestApp(const InputParameters & parameters) : MooseApp(parameters)
{
  th_2DTestApp::registerAll(
      _factory, _action_factory, _syntax, getParam<bool>("allow_test_objects"));
}

th_2DTestApp::~th_2DTestApp() {}

void
th_2DTestApp::registerAll(Factory & f, ActionFactory & af, Syntax & s, bool use_test_objs)
{
  th_2DApp::registerAll(f, af, s);
  if (use_test_objs)
  {
    Registry::registerObjectsTo(f, {"th_2DTestApp"});
    Registry::registerActionsTo(af, {"th_2DTestApp"});
  }
}

void
th_2DTestApp::registerApps()
{
  registerApp(th_2DApp);
  registerApp(th_2DTestApp);
}

/***************************************************************************************************
 *********************** Dynamic Library Entry Points - DO NOT MODIFY ******************************
 **************************************************************************************************/
// External entry point for dynamic application loading
extern "C" void
th_2DTestApp__registerAll(Factory & f, ActionFactory & af, Syntax & s)
{
  th_2DTestApp::registerAll(f, af, s);
}
extern "C" void
th_2DTestApp__registerApps()
{
  th_2DTestApp::registerApps();
}
