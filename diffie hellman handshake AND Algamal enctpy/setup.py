from distutils.core import setup, Extension

module = Extension("ElGamal_c", sources=["encryptmodule.c"]
                  #  ,extra_compile_args=['/openmp']
                   )

setup(name="PackageName",
      version="0.1",
      description="This module is for csc281 project ",
      ext_modules=[module])

