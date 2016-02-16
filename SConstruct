
env = Environment(CCFLAGS = ['-O2','-DRENDER_INFO','-std=c++11'])
env.Replace(CXX = "g++-4.8")

#env.Replace(CXXCOMSTR = "Compiling $TARGET")
#env.Replace(SHCXXCOMSTR = "Compiling $TARGET")
#env.Replace(CCCOMSTR = "Compiling $TARGET")
#env.Replace(SHCCCOMSTR = "Compiling $TARGET")
#env.Replace(LINKCOMSTR = "Linking $TARGET")
#env.Replace(SHLINKCOMSTR = "Linking $TARGET")

env['ROOT'] = '/home/user/git/ClosestPointQuery/src'
env['CORE'] = env['ROOT'] + '/core' 
env['HOUDINI'] = env['ROOT'] + '/houdini'

print env['ROOT']
print env['CORE']
print env['HOUDINI']

env.Append(CCFLAGS=['-I'+env['ROOT']])
env.Append(CCFLAGS=['-isystem','/opt/houdini/toolkit/include'])

SConscript('src/SConscript', variant_dir='debug', exports={'env':env})