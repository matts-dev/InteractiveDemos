include(FetchContent)

macro(EngineLinkIMGUI TARGET ACCESS)
    FetchContent_Declare(
        imgui
        GIT_REPOSITORY https://github.com/DependencyMaster/imgui.git
        GIT_TAG v1.80
    )

    FetchContent_GetProperties(imgui)

    if (NOT imgui_POPULATED)
        FetchContent_Populate(imgui)
        #add_subdirectory("${imgui_SOURCE_DIR}" ${imgui_BINARY_DIR} EXCLUDE_FROM_ALL) #does not contain a CMakeLists.txt file.
    endif()
    # ------TODO -------- 
    # todo - make sure the imgui library is excluded from all, so that it isn't in the project. But where to do that. 
    # todo - how to handle the glad loader on emscripten
    # todo - RENAME SO THIS ISNT LINK -- SHOULD BE SPECIFIC TO ENGINE! this is just a helper for engine, since it needs engine relative paths to work around things. 
    # todo - perhaps move this file, after renaming, to a folder within the engine project.

    #--------------------------------------------------------------------
    # Set up IMGUI as a cmake library, since it lacks cmakelists.txt
    #--------------------------------------------------------------------

    add_library(
        imgui 
        STATIC 
        EXCLUDE_FROM_ALL # don't show up in project view in IDEs
        ${imgui_SOURCE_DIR}/imgui.cpp
        ${imgui_SOURCE_DIR}/imgui_widgets.cpp
        ${imgui_SOURCE_DIR}/imgui_draw.cpp
        ${imgui_SOURCE_DIR}/imgui_tables.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
    )

    target_include_directories(imgui PUBLIC
        "${imgui_SOURCE_DIR}"
        "${imgui_SOURCE_DIR}/backends"
    )


    if(NOT HTML_BUILD) 
        #imgui needs to be able to include glfw, etc.
    	include(${SHARED_CMAKE_UTILITES_DIR}/LinkGLFW.cmake) 
	    LinkGLFW(imgui PUBLIC)

	    #only build this on desktop; emscripten will use the headers included with emscripten expose opengl functions
        Message(STATUS "imgui will use glad.")
	    include(${SHARED_CMAKE_UTILITES_DIR}/LinkGLAD.cmake) 
	    LinkGLAD(imgui PUBLIC)
        #target_compile_options( imgui PRIVATE -DIMGUI_IMPL_OPENGL_LOADER_GLAD) #using custom loader to enable glad and gles2

        #work around glad+es2 windows issues by using a custom loader.
        #TODO rename this so that is obvious it is part of the engine cmakelists txt
        #set(IMGUI_LOADER_WORKAROUND_PATH "Libraries/Engine/src/public/include/ThirdParty/Imgui/DesktopGLES2LoaderWorkaround.h")
        set(IMGUI_LOADER_WORKAROUND_FILE DesktopGLES2LoaderWorkaround.h)
        set(IMGUI_LOADER_WORKAROUND_PATH "${CMAKE_CURRENT_LIST_DIR}/src/public/include/ThirdParty/Imgui/")
        #message(STATUS "imgui debugging loader work around path ${IMGUI_LOADER_WORKAROUND_PATH}") #debug path
        target_include_directories(imgui PRIVATE ${IMGUI_LOADER_WORKAROUND_PATH} )#make sure it can be included
        target_compile_options( imgui PRIVATE -DIMGUI_IMPL_OPENGL_LOADER_CUSTOM=\"${IMGUI_LOADER_WORKAROUND_FILE}\")
    endif()
    #target_compile_options( imgui PRIVATE -DIMGUI_IMPL_OPENGL_ES2) # (WARNING: this causes issues with glad on desktop) dont have imgui call functions not available in gles2 (PROBLEM this seems to short circuit usage of glad)
    
    #--------------------------------------------------------------------
    #debug compile option flags
    #get_target_property(MAIN_CFLAGS imgui COMPILE_OPTIONS)
    #message(STATUS "imgui -- Target compiler flags are: ${MAIN_CFLAGS}")
    #--------------------------------------------------------------------
    

    #--------------------------------------------------------------------
    # link library into the target calling this 
    #--------------------------------------------------------------------
    target_link_libraries(${TARGET} ${ACCESS} imgui)
    target_compile_options( ${TARGET} ${ACCESS} -DWITH_IMGUI=1) #switch to enable/disable code around imgui

    

endmacro()
