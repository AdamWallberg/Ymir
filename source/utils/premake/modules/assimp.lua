ASSIMP_DIR = "$(SolutionDir)utils/deps/assimp-3.3.1/"

function enable_assimp()
	includedirs {ASSIMP_DIR .. "include/"}

	libdirs {ASSIMP_DIR .. "lib/$(Platform)/$(Configuration)"}
	
	configuration {}

	links {"assimp-vc140-mt.lib"}
end