
workspace "BlackJack"
   architecture "x64"
   configurations { "Debug", "Release" }
   startproject "BlackJack"
   location "build"
   libdirs{"."}

project "BlackJack"
kind "ConsoleApp"
   language "C++"
   cppdialect "C++17"
   files
   {
      "IGames.h",
      "IPlayer.h",
      "ITable.h",
      "rules.h",

      "JGame.h",
      "JGame.cc",
      "JPlayer.h",
      "JPlayer.cc",
      "JTable.h",
      "JTable.cc",
      "main.cc",
      "premake5.lua",
   }