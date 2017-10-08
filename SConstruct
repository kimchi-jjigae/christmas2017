import os
from sconstools import environment

#the environment for the whole project
env = Environment()

#linux specific?
env['ENV']['TERM'] = os.environ['TERM']

#setup project parameters
project_name = 'spring_template'
env['project_name'] = project_name
arguments = ARGUMENTS

env['data_folder'] = 'assets'

system_libraries = []
if os.environ.get('EMSDK') is None:
    system_libraries = ['SDL2', 'SDL2_mixer']

system_libraries_paths = []
cpp_defines = {}
cpp_flags = ['-Wall', '-Wextra', '-Wshadow', '-Werror', '-Wconversion', '-Wno-long-long', '-Wno-unused-parameter', '-Wno-unused-variable', '-Wno-unused-function', '-Wno-format-pedantic', '-Wno-conversion', '-Wno-format']
cxx_flags = ['-std=c++14']

environment.cpp_environment_with_tests(env,
    project_name,
    arguments,
    system_libraries,
    system_libraries_paths,
    cpp_defines,
    cpp_flags,
    cxx_flags
    )
