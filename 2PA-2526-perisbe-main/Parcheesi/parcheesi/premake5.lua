-- premake5.lua
workspace "Parcheesi"
   architecture "x64"
   configurations { "Debug", "Release" }
   startproject "Parcheesi"
   location "build"
   libdirs {"lib"}
   includedirs {"include"}

project "ParcheesiJPlayer"
   kind "StaticLib"
   language "C++"
   cppdialect "C++17"
   files { "include/JPlayer.h", "src/JPlayer.cc"}
   includedirs {"include"}

project "ParcheesiJBoard"
   kind "StaticLib"
   language "C++"
   cppdialect "C++17"
   files { "src/JParcheesi.cc", "include/JParcheesi.h" }
   includedirs {"include"}

project "Parcheesi"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++17"
   links {"ParcheesiJPlayer", "ParcheesiJBoard", "PlayerArnau"}
   libdirs {"lib"}
   includedirs {"include"}

   files
   {
      "include/game.h",
      "include/interface/iparcheesi.h",
      "include/PlayerArnau.h",
      "src/game.cc",
      "src/main.cc"
   }