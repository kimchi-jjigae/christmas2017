import os

# parse arguments
all = ARGUMENTS.get('all', '0')
debug = ARGUMENTS.get('debug', '0')
profile = ARGUMENTS.get('profile', '0')
release = ARGUMENTS.get('release', '0')

# if no profile is selected, select release
if debug == '0' and profile == '0' and release == '0':
    release = '1'

if all != '0':
    release = '1'
    debug = '1'
    profile = '1'

# Set our required libraries
libraries 		= ['SDL2', 'SDL2_mixer']
library_paths 	= ['.']
cppDefines 		= {}
cppFlags 		= ['-Wall', '-Wextra', '-Wshadow', '-Werror', '-Wconversion', '-Wno-long-long', '-Wno-unused-parameter', '-Wno-unused-variable', '-Wno-unused-function', '-Wno-format-pedantic', '-Wno-conversion']
cxxFlags 		= ['-std=c++14']

# define the attributes of the build environment shared between
# both the debug and release builds
common_env = Environment()
common_env.Append(LIBS 			= libraries)
common_env.Append(LIBPATH 		= library_paths)
common_env.Append(CPPDEFINES 	= cppDefines)
common_env.Append(CPPFLAGS 		= cppFlags)
common_env.Append(CXXFLAGS 		= cxxFlags)
common_env.Append(depot_dir = "#depot/")
common_env.Append(mode = None)
common_env.Append(first_include = False)
common_env.Append(first_mode_include = False)
common_env['ENV']['TERM'] = os.environ['TERM']

# Define all envs
envs = {}

if debug != 0:
    debug_env = common_env.Clone()
    debug_env.Append(CPPDEFINES=[''])
    debug_env.Append(CXXFLAGS=['-g'])
    envs['debug'] = debug_env

if profile != 0:
    profile_env = common_env.Clone()
    profile_env.Append(CPPDEFINES=[''])
    profile_env.Append(CXXFLAGS=['-g', '-O2'])
    envs['profile'] = profile_env

if release != 0:
    release_env = common_env.Clone()
    release_env.Append(CPPDEFINES=['NDEBUG'])
    release_env.Append(CXXFLAGS=['-O3'])
    envs['release'] = release_env

# Now that all build environment have been defined, let's iterate over
# them and invoke the lower level SConscript files.

first_include = True
for mode, env in envs.iteritems():
    modeDir = 'build/%s' % mode
    env['mode'] = mode
    env['first_include'] = first_include
    env['first_mode_include'] = True
    env.SConscript('SConscript', exports=['env'], variant_dir=modeDir + '/spring_template', src_dir='.', duplicate=0)
    first_include = False
