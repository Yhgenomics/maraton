#!/bin/sh
cd src
rm -rf cmakebuild/
CMaker project:maraton ft:*.h,*.cpp,*.hpp,*.cc,*.c flag:-Wall-std=c++11-pthread
cd cmakebuild
cmake .
make
cp maraton ../../
cd ../../
chmod 777 maraton