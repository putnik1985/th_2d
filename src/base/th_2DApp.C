#include "th_2DApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "ModulesApp.h"
#include "MooseSyntax.h"

InputParameters
th_2DApp::validParams()
{
  InputParameters params = MooseApp::validParams();
  params.set<bool>("use_legacy_material_output") = false;
  params.set<bool>("use_legacy_initial_residual_evaluation_behavior") = false;
  return params;
}

th_2DApp::th_2DApp(const InputParameters & parameters) : MooseApp(parameters)
{
  th_2DApp::registerAll(_factory, _action_factory, _syntax);
}

th_2DApp::~th_2DApp() {}

void
th_2DApp::registerAll(Factory & f, ActionFactory & af, Syntax & syntax)
{
  ModulesApp::registerAllObjects<th_2DApp>(f, af, syntax);
  Registry::registerObjectsTo(f, {"th_2DApp"});
  Registry::registerActionsTo(af, {"th_2DApp"});

  /* register custom execute flags, action syntax, etc. here */
}

void
th_2DApp::registerApps()
{
  registerApp(th_2DApp);
}

/***************************************************************************************************
 *********************** Dynamic Library Entry Points - DO NOT MODIFY ******************************
 **************************************************************************************************/
extern "C" void
th_2DApp__registerAll(Factory & f, ActionFactory & af, Syntax & s)
{
  th_2DApp::registerAll(f, af, s);
}
extern "C" void
th_2DApp__registerApps()
{
  th_2DApp::registerApps();
}
