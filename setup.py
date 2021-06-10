
import sys

from skbuild import setup

setup(
    name="p56-measurement",
    version="1.0.0",
    description="active speech level and the active speech factor measured using ITU P.56 measurement metodology",
    author="Marcin Kuropatwiński",
    license="GNU 3.0",
    packages=["p56"],
    install_requires=["cython"],
    )
