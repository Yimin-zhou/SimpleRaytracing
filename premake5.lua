-- premake5.lua
workspace "SimpleRaytracing"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }
   startproject "SimpleRaytracing"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
include "Walnut/WalnutExternal.lua"

include "SimpleRaytracing"