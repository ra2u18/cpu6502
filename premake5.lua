workspace "cpuemulate"
    startproject "cpueditor"
    architecture "x64"

    configurations 
    {
        "Debug",
        "Release",
    }

-- External Dependencies
externals = {}
externals["spdlog"] = "external/spdlog"

tdir = "bin/%{cfg.buildcfg}/%{prj.name}"        -- target directory
odir = "bin-obj/%{cfg.buildcfg}/%{prj.name}"    -- obj directory

project "cpu6205"
    location "cpu6205"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir(tdir)
    objdir(odir)

    -- Files to include in the project
    files
    {
        "%{prj.name}/include/**.h",     -- exposed library functionality
        "%{prj.name}/src/**.h",         -- libraries embedded in the .lib file that the user can't see
        "%{prj.name}/src/**.cpp",       
    }

    sysincludedirs
    {
        "%{prj.name}/include/cpu6205",
        "%{externals.spdlog}/include"
    }

    flags "FatalWarnings"

    -- Windows
    filter {"system:windows", "configurations:*"}
        systemversion "latest" -- target latest windows upgrade when "cli gensln"
        defines{ "C6205_PLATFORM_WINDOWS" }

    -- [CONFIGURATION DEFINES]: usually used to turn on optimization
    filter "configurations:Debug"
        defines "C6205_CONFIG_DEBUG"
        runtime "Debug"
        symbols "on" -- pdb symbols / for release we don't want them

    filter "configurations:Release"
        defines "C6205_CONFIG_RELEASE"
        runtime "Release"
        symbols "off"
        optimize "on"

project "cpueditor"
    location "cpueditor"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"
    links "cpu6205"

    targetdir(tdir)
    objdir(odir)

    -- Files to include in the project
    files
    {
        "%{prj.name}/src/**.h", -- code under source
        "%{prj.name}/src/**.cpp",
    }

    sysincludedirs
    {
        "cpu6205/include",
    }

    flags
    {
        "FatalWarnings" -- useful for cross-platform programming
    }
    
    -- [CONFIGURATION DEFINES]: usually used to turn on optimization
    filter "configurations:Debug"
        defines "C6205_CONFIG_DEBUG"
        runtime "Debug"
        symbols "on" -- pdb symbols / for release we don't want them

    filter "configurations:Release"
        defines "C6205_CONFIG_RELEASE"
        runtime "Release"
        symbols "off"
        optimize "on"