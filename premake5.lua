workspace "Maple"
	architecture "x64"
	startproject "Sandbox"
	
	configurations {
		"Debug",
		"Release",
		"Dist"
	}
	
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Other directories that we want to include in our projects
includeDirs = {}
includeDirs["GLFW"] = "Maple/vendor/GLFW/include"
includeDirs["glad"] = "Maple/vendor/glad/include"
includeDirs["spdlog"] = "Maple/vendor/spdlog/include"
includeDirs["ImGui"] = "Maple/vendor/imgui"
includeDirs["glm"] = "Maple/vendor/glm"
includeDirs["stb_image"] = "Maple/vendor/stb_image"

-- Include extra premake files that we want to execute
include "Maple/vendor/GLFW"
include "Maple/vendor/glad"
include "Maple/vendor/imgui"

project "Maple"
	location "Maple"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	pchheader "mppch.h"
	pchsource "Maple/src/mppch.cpp"
	
	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}
	
	defines {
		"_CRT_SECURE_NO_WARNINGS"
	}
	
	includedirs {
		"%{prj.name}/src",
		"%{includeDirs.spdlog}",
		"%{includeDirs.GLFW}",
		"%{includeDirs.glad}",
		"%{includeDirs.ImGui}",
		"%{includeDirs.glm}",
		"%{includeDirs.stb_image}"
	}
	
	links {
		"GLFW",
		"glad",
		"ImGui",
		"opengl32.lib"
	}
	
	filter "system:windows"
		systemversion "latest"
		
		defines {
			"MP_PLATFORM_WINDOWS",
			"MP_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}
		
	filter "configurations:Debug"
		defines "MP_DEBUG"
		runtime "Debug"
		symbols "on"
	
	filter "configurations:Release"
		defines "MP_RELEASE"
		runtime "Release"
		optimize "on"
	
	filter "configurations:Dist"
		defines "MP_DIST"
		runtime "Release"
		optimize "on"
		
project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	
	includedirs {
		"Maple/src",
		"Maple/vendor",
		"%{includeDirs.spdlog}",
		"%{includeDirs.glm}"
	}
	
	links {
		"Maple"
	}
	
	filter "system:windows"
		systemversion "latest"
		
		defines {
			"MP_PLATFORM_WINDOWS"
		}
		
	filter "configurations:Debug"
		defines "MP_DEBUG"
		runtime "Debug"
		symbols "on"
	
	filter "configurations:Release"
		defines "MP_RELEASE"
		runtime "Release"
		optimize "on"
	
	filter "configurations:Dist"
		defines "MP_DIST"
		runtime "Release"
		optimize "on"
