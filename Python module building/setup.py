from distutils.core import setup, Extension

module = Extension("MyPrime", sources=["primemodule.c"])

setup(name="PackageName",
      version="0.1",
      description="This module is for csc281 project ",
      ext_modules=[module])

