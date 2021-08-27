from setuptools import setup, Extension
import os
import pybind11
import win32.win32api
import win32com

#cwd = os.path.dirname(os.path.abspath(__file__))
#cwd = os.environ.get('SolutionDir')
#cwd = 'c:\\debug\\opcdaaehda-client-solution-cpp\\python\\PythonWrapper'
cwd = os.path.abspath(os.path.dirname(__file__))
include_path = os.path.join(cwd, "..", "..", 'include')
lib_path = os.path.join(cwd, "..", "..", 'x64', 'v142', 'Release')
lib_dll = os.path.join(lib_path, 'TechnosoftwareDaAeHdaClient.dll')

win32_path = os.path.abspath(os.path.dirname(win32.win32api.__file__))
win32_include_path =  os.path.join(win32_path, "include")
win32_libs_path =  os.path.join(win32_path, "libs")

win32com_path = os.path.abspath(os.path.dirname(win32com.__file__))
win32com_include_path =  os.path.join(win32com_path, "include")
win32com_libs_path =  os.path.join(win32com_path, "libs")



def get_win32_include():
    # type: (bool) -> str
    installed_path = os.path.join(DIR, "include")
    source_path = os.path.join(os.path.dirname(DIR), "include")
    return installed_path if os.path.exists(installed_path) else source_path



#cpp_args = ['-std=c++11', '-stdlib=libc++', '-mmacosx-version-min=10.7']
cpp_args = ['/std:c++14', '-stdlib=libc++']

opc_module = Extension(
    'opcdaaehdaclient',
    sources=['module.cpp'],
    include_dirs=[pybind11.get_include(), include_path, win32_include_path, win32com_include_path],
    libraries=['TechnosoftwareDaAeHdaClient'],
    library_dirs=[lib_path, win32_libs_path, win32com_libs_path],
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