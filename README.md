# p56
Implementation of the ITU P.56 active speech RMS power and active speech factor measurement.

# Cloning repository
To clone repository for latter C++ or Python installation run

```
git clone --recurse-submodules https://github.com/mkurop/p56.git
```

# Installation as a C++ library
Run the following in the project root directory

```
mkdir build
cd build
cmake ..
make 
sudo make install
```

In the CMakeLists.txt of your project use:

```
find_package(p56 REQUIRED)
```

# Installation as a Python C++ extension

First create conda environment using

```
conda create --name <env_name> --file requirements.txt
```

Then activate the environment

```
conda activate <env_name>
```

In the folder containing setup.py run

```
pip install .
```

And the package is available in your environment for import.

NOTE: Prior to use of the python extension module, go through the C++ installation (for `libp56.so` library being available in `/usr/local/lib64/`)

# Usage C++
Consult the `example/p56-example.cpp` for example usage.

# Usage Python
Consult the `example-python/p56-example.py` for example usage.
