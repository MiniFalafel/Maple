workspace "Maple"
	architecture "x64"
	
	configurations {
		"Debug",
		"Release",
		"Dist"
	}
	
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Other directories that we want to include in our projects
includeDirs = {}
includeDirs["GLFW"] = "Maple/vendor/GLFW/include"
includeDirs["spdlog"] = "Maple/vendor/spdlog/include"

-- Include extra premake files that we want to execute
include "Maple/vendor/GLFW"

project "Maple"
	location "Maple"
	kind "SharedLib"
	language "C++"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	pchheader "mppch.h"
	pchsource "Maple/src/mppch.cpp"
	
	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	
	includedirs {
		"%{prj.name}/src",
		"%{includeDirs.spdlog}",
		"%{includeDirs.GLFW}"
	}
	
	links {
		"GLFW",
		"opengl32.lib"
	}
	
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		
		defines {
			"MP_PLATFORM_WINDOWS",
			"MP_BUILD_DLL"
		}
		
		postbuildcommands {
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}
		
	filter "configurations:Debug"
		defines "MP_DEBUG"
		buildoptions "/MDd"
		symbols "On"
	
	filter "configurations:Release"
		defines "MP_RELEASE"
		buildoptions "/MD"
		optimize "On"
	
	filter "configurations:Dist"
		defines "MP_DIST"
		buildoptions "/MD"
		optimize "On"
		
project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	
	includedirs {
		"Maple/vendor/spdlog/include",
		"Maple/src"
	}
	
	links {
		"Maple"
	}
	
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		
		defines {
			"MP_PLATFORM_WINDOWS",
		}
		
	filter "configurations:Debug"
		defines "MP_DEBUG"
		buildoptions "/MDd"
		symbols "On"
	
	filter "configurations:Release"
		defines "MP_RELEASE"
		buildoptions "/MD"
		optimize "On"
	
	filter "configurations:Dist"
		defines "MP_DIST"
		buildoptions "/MD"
		optimize "On"