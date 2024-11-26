from setuptools import setup, Extension

module = Extension(
    "myWav_module",           # Module name
    sources=["myWav_module.c"]  # C source file
)

setup(
    name="myWav_module",
    version="1.0",
    description="A module for splitting and combining WAV files.",
    ext_modules=[module],
)
