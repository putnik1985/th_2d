
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
[]

[ICs]
  [init_temps]
    type = FunctionIC
    variable = T
    function = 'if(y>0.333,if(y<0.6665, if(x>0.8335, if(x<1.1665, 268.15, 278.15), 278.15), 278.15), 278.15)'
  []
[]

[Kernels]
 [conduction]
  type = Diffusion_NP
  variable = T
  T0 = 273.15
  Tf = 269.15
  lambda_frozen = 2.41
  lambda_unfrozen = 3.46
 []
  
 [time_derivative]
  type = HeatConductionTimeDerivative
  variable = T
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
[]

[Materials]
 [thermal]
  type = GenericConstantMaterial
  prop_names = 'thermal_conductivity specific_heat density'
  prop_values = '4.0 4000.0 1000.0'
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

