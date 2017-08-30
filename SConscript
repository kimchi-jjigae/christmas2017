from sconstools import dependencies
from sconstools import glob

Import('env')

env = env.Clone()
mode = env['mode']
project_name = env['project_name']
depot_dir =  env['depot_dir']

##add dophax building and build our dpx file
returned = dependencies.include_conscript(env, '#dependencies/dophax')
env.Append(BUILDERS = {'DophaxGen' : returned['builder']})
env.Append(SCANNERS = returned['scanner'])

env.DophaxGen(target = [], source = ['game.dpx'], WRAP_DIR='build/' + mode + '/' + project_name + '/')

##gather all source files
sources = []
#normal sources
sources.extend(glob.recursive_glob(env, 'src', '*.cpp'))
env.Append(CPPPATH=['src/'])
#dophax generated sources
sources.extend(glob.recursive_glob(env, '#build/' + mode + '/' + project_name + '/generated', '*.cpp'))
env.Append(CPPPATH=['#build/' + mode + '/' + project_name + '/generated'])

##declare dependencies
#include them
dependencies.include_conscript(env, '#dependencies/lodepng')
dependencies.include_conscript(env, '#dependencies/spring')
dependencies.include_conscript(env, '#dependencies/glades2')
dependencies.include_conscript(env, '#dependencies/imgui')
dependencies.include_conscript(env, '#dependencies/thero')

#use them
dependencies.use_lib(env = env, lib_name = 'spring')
dependencies.use_lib(env = env, lib_name = 'lodepng')
dependencies.use_lib(env = env, lib_name = 'dophax')
dependencies.use_lib(env = env, lib_name = 'imgui')
dependencies.use_lib(env = env, lib_name = 'glades2')
dependencies.use_lib(env = env, lib_name = 'thero', headers_only = True)

#add generated files as includes
env.Append(CPPPATH=['#build/' + mode + '/spring/generated'])

##build our application
binary = env.Program(target = project_name + '_' + mode, source = sources, duplicate=0)

#move to bin
env.Install('#bin', binary)

###tests

if env['build_tests']:
    tests_env = env.Clone()
    
    test_sources = []
    test_sources.extend(glob.recursive_glob(env, 'tests', '*.cpp'))
    test_sources.extend(Glob('src/gamedata.o'))
    test_sources.extend(Glob('src/tostring.o'))
    test_sources.extend(glob.recursive_glob(env, 'src/*', '*.o'))
    test_sources.extend(glob.recursive_glob(env, 'generated', '*.o'))
    
    dependencies.include_conscript(tests_env, '#dependencies/catch')
    dependencies.use_lib(env = tests_env, lib_name = 'catch', headers_only = True)
    
    tests = tests_env.Program(target = project_name + '_tests_' + mode, source = test_sources, duplicate=0)
    env.Install('#bin', tests)
