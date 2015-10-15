#!/bin/sh
rm -rf cmakebuild/
CMaker project:maraton ft:*.h,*.cpp,*.hpp,*.cc,*.c flag:-Wall-std=c++11-pthread auto
cd cmakebuild
cmake .
make
cp maraton ../