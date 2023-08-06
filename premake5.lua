-- MyEngine

workspace "MyEngine"
    architecture "x64"

    configurations
    {
        "Debug",
        "RelWithDebInfo",
        "Release"
    }

project "MyEngine"
    location "./"
    kind "SharedLib"
    language "C++"

    targetdir ("bin/Debug/MyEngine")
    objdir ("obj/Debug/MyEngine")

    files
    {
        "include/**.hpp",
        "src/**.cpp"
    }

    includedirs
    {
        "external/spdlog/include",
        "include"
    }

    filter "system:windows"
        cppdialect "C++20"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "MYENGINE_PLATFORM_WINDOWS",
            "MYENGINE_BUILD_DLL"
        }

        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} bin/%{cfg.buildcfg}/ExampleApp")
        }
    
    filter "configurations:Debug"
        defines "MYENGINE_DEBUG"
        symbols "On"
    
    filter "configurations:RelWithDebInfo"
        defines "MYENGINE_RELWITHDEBINFO"
        optimize "On"
    
    filter "configurations:Release"
        defines "MYENGINE_RELEASE"
        optimize "On"

project "ExampleApp"
    location "examples/ExampleApp"
    kind "ConsoleApp"
    language "C++"

    targetdir ("bin/%{cfg.buildcfg}/ExampleApp")
    objdir ("obj/%{cfg.buildcfg}/ExampleApp")

    files
    {
        "examples/ExampleApp/src/**.cpp"
    }

    includedirs
    {
        "external/spdlog/include",
        "include"
    }

    links
    {
        "MyEngine"
    }

    filter "system:windows"
        cppdialect "C++20"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "MYENGINE_PLATFORM_WINDOWS"
        }
    
    filter "configurations:Debug"
        defines "MYENGINE_DEBUG"
        symbols "On"
    
    filter "configurations:RelWithDebInfo"
        defines "MYENGINE_RELWITHDEBINFO"
        optimize "On"
    
    filter "configurations:Release"
        defines "MYENGINE_RELEASE"
        optimize "On"
