
set(VERITA_SOURCE
    ${VERITA_SOURCE_DIR}/Game.cpp
    ${VERITA_SOURCE_DIR}/log.cpp
    ${VERITA_SOURCE_DIR}/ResourcePool.cpp

    # ${VERITA_SOURCE_DIR}/entrypoint.cpp
)

set(VERITA_HEADERS
    ${VERITA_SOURCE_DIR}/include/VeritaSTG/CallbackRegistry.hpp
    ${VERITA_SOURCE_DIR}/include/VeritaSTG/Game.hpp
    ${VERITA_SOURCE_DIR}/include/VeritaSTG/GlobalEventContext.hpp
    ${VERITA_SOURCE_DIR}/include/VeritaSTG/Resource.hpp
    ${VERITA_SOURCE_DIR}/include/VeritaSTG/ResourceEngineWrapper.hpp
    ${VERITA_SOURCE_DIR}/include/VeritaSTG/ResourcePool.hpp
    
    ${VERITA_SOURCE_DIR}/include/VeritaSTG/log.hpp
    ${VERITA_SOURCE_DIR}/include/VeritaSTG/engine_panic.hpp
)

set(VERITA_FRAMEWORK_SOURCE
    ${VERITA_FRAMEWORKS_DIR}/audio/audio.c
    ${VERITA_FRAMEWORKS_DIR}/glad/src/gl.c
)

find_path(GLFW_INCLUDE_DIR GLFW/glfw3.h)
find_path(FMT_INCLUDE_DIR fmt/core.h)

set(VERITA_INCLUDE
# Framework Include Directories ===============================================
    ${VERITA_FRAMEWORKS_DIR}
    ${VERITA_FRAMEWORKS_DIR}/audio

    ${VERITA_FRAMEWORKS_DIR}/glad/include
    ${VERITA_FRAMEWORKS_DIR}/Boxer/include

    ${Boost_INCLUDE_DIR}
    ${FMT_INCLUDE_DIR}
    ${GLFW_INCLUDE_DIR}

# VeritaSTG Include Directories ===============================================
    ${VERITA_SOURCE_DIR}/include/
)
