workspace "AirportProject"
    configurations { "Debug", "Release" }
    platforms { "x86", "x64" }

project "Airport"
    location "Airport"
    kind "ConsoleApp"
    language "C++"
    clr "On"
    dotnetframework ("4.7.2")

    targetdir "bin/%{cfg.buildcfg}"
    objdir "bin-int/%{cfg.buildcfg}"

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/src/**.resx"
    }

    includedirs {
        "%{prj.name}/src",
        "%{prj.name}/vendor",
        "%{prj.name}/packages/MaterialSkin.0.2.1",
        "Properties/**.resx"  
    }

    links {  
        "System.dll",   
        "System.Data.dll",
        "System.Windows.Forms.dll", 
        "System.Drawing.dll",
        "C:/dev/Airport/packages/MaterialSkin.0.2.1/lib/MaterialSkin.dll"
    }     
    
    flags {
        "MultiProcessorCompile"
    }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"
        optimize "Off"
        runtime "Debug"
    
    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"
        runtime "Release"
    
    filter "platforms:x86"
        architecture "x86"
        buildoptions {
            "/clr",
            "/EHa"
        }
        
    filter "platforms:x64"
        architecture "x64"
        buildoptions {
            "/clr",
            "/EHa"
        }
        
    vpaths {
        ["Headers/*"] = { "**.h", "**.hpp" },
        ["Sources/*"] = { "**.cpp" },
        ["Resources/*"] = { "**.resx" },
        ["Properties/*"] = { "Properties/**.resx" }
    }

    defines {
        "_UNICODE",
        "UNICODE"
    }

    entrypoint "main"
        