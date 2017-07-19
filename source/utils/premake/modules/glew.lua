GLEW_DIR = "$(SolutionDir)utils/deps/glew-2.0.0/"

function enable_glew()
	includedirs { GLEW_DIR .. "include/" }
	libdirs { GLEW_DIR .. "lib/Release/$(Platform)/" }
	links { "opengl32.lib", "glew32s.lib" }
	defines { "GLEW_STATIC" }
end