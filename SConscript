from sconstools import dependencies

Import('env')

env = env.Clone()

env.Append(CPPPATH=['src'])

returned = dependencies.include_conscript(env, '#dependencies/dophax')

env.Append(BUILDERS = {'DophaxGen' : returned['builder']})
env.Append(SCANNERS = returned['scanner'])

mode = env['mode']
depot_dir =  env['depot_dir']

env.DophaxGen(target = [], source = ['spring_template.dpx'], WRAP_DIR='build/' + mode + '/spring_template/');

sources = []
sources.extend(Glob('src/*.cpp'))
sources.extend(Glob('src/*/*.cpp'))
sources.extend(Glob('src/*/*/*.cpp'))
sources.extend(Glob('src/*/*/*/*.cpp'))

#might be a better way to handle these automatically
sources.extend(Glob('#build/' + mode + '/spring_template/generated/*.cpp'))
sources.extend(Glob('#build/' + mode + '/spring_template/generated/*/*.cpp'))
sources.extend(Glob('#build/' + mode + '/spring_template/generated/*/*/*.cpp'))
env.Append(CPPPATH=['#build/' + mode + '/spring_template/generated'])

dependencies.include_conscript(env, '#dependencies/spring')
dependencies.include_conscript(env, '#dependencies/glades2')
dependencies.include_conscript(env, '#dependencies/lodepng')
dependencies.include_conscript(env, '#dependencies/imgui')
dependencies.include_conscript(env, '#dependencies/thero')

dependencies.use_lib(env = env, lib_name = 'spring')
dependencies.use_lib(env = env, lib_name = 'dophax')
dependencies.use_lib(env = env, lib_name = 'thero', headers_only = True)
env.Append(CPPPATH=['#build/' + mode + '/spring/generated'])

dependencies.use_lib(env = env, lib_name = 'imgui')
dependencies.use_lib(env = env, lib_name = 'glades2')
dependencies.use_lib(env = env, lib_name = 'lodepng')

headers = []
headers.extend(Glob('src/*.hpp'))
headers.extend(Glob('src/*/*.hpp'))
headers.extend(Glob('src/*/*/*.hpp'))
headers.extend(Glob('src/*/*/*/*.hpp'))

binary = env.Program(target = 'spring_template_' + mode, source = sources, duplicate=0)

env.Install('#bin', binary)
