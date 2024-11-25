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
        "%{prj.name}/vendor/assimp/include",
        "%{prj.name}/packages/MaterialSkin.0.2.1",
        "Properties/**.resx",
    }

    libdirs {
        "%{prj.name}/vendor/assimp/lib/Debug",
        "%{prj.name}/vendor/GL/lib/Debug",
        "%{prj.name}/vendor/SOIL-master/Debug",
        "C:/dev/Airport/packages/Microsoft.Web.WebView2.1.0.2903.40/build/native/arm64"
    }

    links {  
        "%{prj.name}/vendor/assimp/bin/Debug/assimp-vc143-mtd.dll",
        "System.dll",   
        "System.Data.dll",
        "System.Windows.Forms.dll", 
        "System.Drawing.dll",
        "C:/dev/Airport/packages/MaterialSkin.0.2.1/lib/MaterialSkin.dll",
        "assimp-vc143-mtd.lib",
        "soil.lib",
        "WebView2Loader.dll.lib"
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
        