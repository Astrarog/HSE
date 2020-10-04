#!/bin/bash

# clone bake
hg clone http://code.nsnam.org/bake bake
export BAKE_HOME=`pwd`/bake
export PATH=$PATH:$BAKE_HOME
export PYTHONPATH=$PYTHONPATH:$BAKE_HOME

# intall dce
mkdir dce
cd dce
bake.py configure -e dce-ns3-1.9
bake.py download
bake.py build -vvv

# finish

whoami
printenv

