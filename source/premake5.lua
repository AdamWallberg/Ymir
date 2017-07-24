require "modules/glew"
require "modules/glfw"
require "modules/assimp"
require "modules/soil"

solution("YmirSolution")
	language "C++"
	debugdir "$(OutDir)"
	objdir "build/"
	targetdir "$(SolutionDir)../app/"
	targetname "$(ProjectName)_$(Configuration)_$(Platform)"
	systemversion "10.0.14393.0" 
	
	configurations {
		"Debug",
		"Release",
	}
	
	platforms {
		"Win32",
		"x64",
	}
	
	configuration "Debug"
		symbols "On"
		defines {
			"DEBUG",
		}
		
	configuration "Release"
		optimize "On"
		defines {
			"RELEASE",
			"NDEBUG",
		}
	
	configuration {}
	
	linkoptions {
		--"/NODEFAULTLIB:MSVCRT",
		"/NODEFAULTLIB:LIBCMT",
		"/ignore:4099",
	}
	
project("Ymir")
	kind "ConsoleApp"
	
	includedirs {
		"code/",
	}
	
	files {
		"code/**.cpp",
		"code/**.h",
		"code/**.hpp",
	}
	
	enable_glew()
	enable_glfw()
	enable_assimp()
	enable_soil()