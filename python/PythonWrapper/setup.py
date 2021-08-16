from setuptools import setup, Extension
import os
import pybind11


#cwd = os.path.dirname(os.path.abspath(__file__))
#cwd = os.environ.get('SolutionDir')
cwd = 'c:\\debug\\opcdaaehda-client-solution-cpp\\python\\PythonWrapper'
include_path = os.path.join(cwd, "..", "..", 'include')
lib_path = os.path.join(cwd, "..", "..", 'x64', 'v142', 'Release')
lib_dll = os.path.join(lib_path, 'TechnosoftwareDaAeHdaClient.dll')

#cpp_args = ['-std=c++11', '-stdlib=libc++', '-mmacosx-version-min=10.7']
cpp_args = ['/std:c++14', '-stdlib=libc++']

opc_module = Extension(
    'opcdaaehdaclient',
    sources=['module.cpp'],
    include_dirs=[pybind11.get_include(), include_path],
    libraries=['TechnosoftwareDaAeHdaClient'],
    library_dirs=[lib_path],
    language='c++',
    extra_compile_args=cpp_args,
    )

setup(
    name='opcdaaehdaclient',
    version='1.0',
    description='Python package with opcdaaehdaclient C++ extension (PyBind11)',
    ext_modules=[opc_module],
    data_files=[(
        'lib\\site-packages\\', [lib_dll]
    )],
)