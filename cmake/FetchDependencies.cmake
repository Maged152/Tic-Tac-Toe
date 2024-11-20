include(FetchContent)

####################################### Fetch raylib #######################################
FetchContent_Declare(
  raylib
  GIT_REPOSITORY https://github.com/raysan5/raylib.git
  GIT_TAG 5.0
  GIT_SHALLOW    TRUE
)

set(BUILD_EXAMPLES OFF CACHE BOOL "Disable examples" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "static build" FORCE)

FetchContent_MakeAvailable(raylib)