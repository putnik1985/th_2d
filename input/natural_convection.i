
[Mesh]
  [domain]
    type = GeneratedMeshGenerator
    dim = 2
    nx = 64
    ny = 32
    xmin = 0
    xmax = 3.
    ymin = 0
    ymax = 1.
  []
[]

[Variables]
  [T]
  []
  [pw]
  []
  [p]
  []
  [pi]
  []
[]

[ICs]
  [init_temps]
    type = FunctionIC
    variable = T
    function = 'if(y>0.333,if(y<0.6665, if(x>0.8335, if(x<1.1665, 268.15, 278.15), 278.15), 278.15), 278.15)'
  []

  [init_pw]
    type = FunctionIC
    variable = pw
    function = '100000.'
  []
[]

[Kernels]
 [pi_equation]
   type = PI_NP
    ri = 920
    rw = 1000.
    Lf = 334000.
    T0 = 273.15
   variable = pi

   T = T
  pw = pw
 []

 [pore_pressure]
   type = PW_NP
   kappaw = 0.6
   
   variable = pw
   p = p
  pi = pi
 []

 [p_derivative]
  type = PressureDerivative_NP
  bf = 1.e-8
   n = 0.37
     W = 400.
    T0 = 273.15
 swres = 0.05

  variable = p
  coupled = T
 []

 [mass_balance]
     type = Mass_Balance_PW_T_NP
     W = 400.
    T0 = 273.15
 swres = 0.05
    ri = 920
    rw = 1000.
    n = 0.37
     k = 7.17e-4
    kr = 1.0e-6
 gammaw = 9805.
  variable = p 
  pw = pw
   T = T
 []

 [conduction]
  type = Diffusion_NP
  variable = T
  T0 = 273.15
  lambdas = 9.0
  lambdaw = 0.6
  lambdai = 2.14
  W = 400.
  n = 0.37
 []
  
 [time_derivative]
     type = TempDerivative_NP
     W = 400.
    T0 = 273.15
 swres = 0.05
    ri = 920
    rs = 2650.
    rw = 1000.
    ci = 2060.
    cs = 835.
    cw = 4182.
    porosity = 0.37
    Lf = 334000.
  variable = T
 []

 [convection]
     type = Convection_NP
     W = 400.
    T0 = 273.15
 swres = 0.05
    ri = 920
    rw = 1000.
    ci = 2060.
    cw = 4182.
     k = 7.17e-4
    kr = 1.0e-6
 gammaw = 9805.
  variable = T
  coupled = pw
 []

[]

[BCs]
 [left]
  type = DirichletBC
  variable = T
  value = 298.
  boundary = left
 []

 [right]
  type = NeumannBC
  variable = T
  value = 0.
  boundary = right
 []

 [top]
  type = NeumannBC
  variable = T
  value = 0.
  boundary = top
 []

 [bottom]
  type = NeumannBC
  variable = T
  value = 0.
  boundary = bottom
 []

 [p_top]
  type = DirichletBC
  variable = p
  value = 100000.
  boundary = top
 []

 [p_bottom]
  type = DirichletBC
  variable = p
  value = 100000.
  boundary = bottom
 []

 [p_left]
  type = DirichletBC
  variable = p
  value = 100000.
  boundary = left
 []

 [p_right]
  type = DirichletBC
  variable = p
  value = 100000.
  boundary = right
 []
[]

[Preconditioning]
  [basic]
    type = SMP
    full = true
    petsc_options_iname = '-pc_type -sub_pc_type -sub_pc_factor_shift_type -pc_asm_overlap'
    petsc_options_value = ' asm      lu           NONZERO                   2'
  []
[]

[Executioner]
  type = Transient
  end_time = 2.e4
  dtmax = 1e3
  nl_rel_tol = 1e-6
  [TimeStepper]
    type = IterationAdaptiveDT
    dt = 100.
  []
[]

[Outputs]
  exodus = true
[]

