SOIL_DIR = "$(SolutionDir)utils/deps/soil/"

function enable_soil()
	includedirs {SOIL_DIR .. "src/"}

	configuration "x64"
		libdirs {SOIL_DIR .. "build/x64/$(Configuration)/"}
		
	configuration "Win32"
		libdirs {SOIL_DIR .. "build/$(Configuration)/"}
	
	configuration{}

	links {"SOIL.lib"}
end