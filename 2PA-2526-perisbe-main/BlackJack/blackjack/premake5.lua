-- premake5.lua
workspace "BlackJack"
   architecture "x64"
   configurations { "Debug", "Release" }
   startproject "BlackJack"
   location "build"
   libdirs {"lib"}
   includedirs {"include"}

project "JPlayer"
   kind "StaticLib"
   language "C++"
   cppdialect "C++17"
   files {"include/JPlayer.h", "src/JPlayer.cc"}
   includedirs {"include"}

project "JTable"
   kind "StaticLib"
   language "C++"
   cppdialect "C++17"
   files {"include/JTable.h", "src/JTable.cc"}
   includedirs {"include"}

project "BlackJack"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++17"
   links {"JPlayer", "JTable"}
   libdirs {"lib"}
   includedirs {"include"}

   files
   {
      "include/IGame.h",
      "include/JGame.h",
      "src/JGame.cc",
      "include/JRules.h",
      "src/main.cc"
   }
