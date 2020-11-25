#!/usr/bin/env python
# encoding: utf-8


__author__ = 'mutalisk'

from setuptools import setup
from distutils.extension import Extension

ext_modules = [Extension("pyX11", ["pyX11/pyX11.cpp", "pyX11/x11/aes_helper.cpp", "pyX11/x11/blake.cpp",
                                   "pyX11/x11/bmw.cpp", "pyX11/x11/cubehash.cpp", "pyX11/x11/echo.cpp",
                                   "pyX11/x11/groestl.cpp", "pyX11/x11/jh.cpp", "pyX11/x11/keccak.cpp",
                                   "pyX11/x11/luffa.cpp", "pyX11/x11/shavite.cpp",
                                   "pyX11/x11/simd.cpp", "pyX11/x11/skein.cpp", "pyX11/x11/x11.cpp"],
    language="c++",
    define_macros=[('_MSC_VER', None), ('_WIN32', None), ('MS_WIN64', None)],
    include_dirs=["pyX11/x11"],
    library_dirs=["pywrapper-dependence/lib64-win"],
    libraries=["python27"]
    )]

setup(name='pyX11',
    version='0.1.0',
    description='Python Wrapper of X11 Algo',
    author='',
    author_email='',
    url='https://github.com/mutalisk999/pyX11',
    platforms='win',
    packages=['pyX11'],
    install_requires=["setuptools"],
    zip_safe=False,
    ext_modules = ext_modules,
    )