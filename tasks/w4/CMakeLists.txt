############################# client #############################

file (GLOB_RECURSE W4_CLIENT_INCLUDE client/*.hpp)
file (GLOB_RECURSE W4_CLIENT_SOURCE client/*.cpp)

add_executable(w4-client)

target_include_directories(w4-client
  PUBLIC
    .
  )

target_sources(w4-client
  PUBLIC
    ${W4_CLIENT_INCLUDE}
  PRIVATE
    ${W4_CLIENT_SOURCE}
  )

target_link_libraries(w4-client
  PUBLIC
    w4-entity
    w4-platform
    w4-network
    w4-protocol
  )

############################# server #############################

file (GLOB_RECURSE W4_SERVER_INCLUDE server/*.hpp)
file (GLOB_RECURSE W4_SERVER_SOURCE server/*.cpp)

add_executable(w4-server)

target_include_directories(w4-server
  PUBLIC
    .
  )

target_sources(w4-server
  PUBLIC
    ${W4_SERVER_INCLUDE}
  PRIVATE
    ${W4_SERVER_SOURCE}
  )

target_link_libraries(w4-server
  PUBLIC
    w4-entity
    w4-network
    w4-protocol
    w4-utils
  )

############################# entity #############################

file(GLOB_RECURSE W4_ENTITY_INCLUDE entity/*.hpp)
file(GLOB_RECURSE W4_ENTITY_SOURCE entity/*.cpp)

add_library(w4-entity)

target_include_directories(w4-entity
  PUBLIC
    .
  )

target_sources(w4-entity
  PUBLIC
    ${W4_ENTITY_INCLUDE}
  PRIVATE
    ${W4_ENTITY_SOURCE}
  )

target_link_libraries(w4-entity
  PUBLIC
    w4-platform
  )

############################# network #############################

file(GLOB_RECURSE W4_NETWORK_INCLUDE network/*.hpp)
file(GLOB_RECURSE W4_NETWORK_SOURCE network/*.cpp)

add_library(w4-network)

target_include_directories(w4-network
  PUBLIC
    .
    ${MULTIPLAYER_SOURCE_DIR}/third_party/enet/include
  )

target_sources(w4-network
  PUBLIC
    ${W4_NETWORK_INCLUDE}
  PRIVATE
    ${W4_NETWORK_SOURCE}
  )

target_link_libraries(w4-network
  PUBLIC
    enet
  )

############################# platform #############################

file(GLOB_RECURSE W4_PLATFORM_INCLUDE platform/*.hpp)
file(GLOB_RECURSE W4_PLATFORM_SOURCE platform/*.cpp)

add_library(w4-platform)

target_include_directories(w4-platform
  PUBLIC
    .
  )

target_sources(w4-platform
  PUBLIC
    ${W4_PLATFORM_INCLUDE}
  PRIVATE
    ${W4_PLATFORM_SOURCE}
  )

target_link_libraries(w4-platform
  PUBLIC
    raylib
  )

############################# protocol #############################

file(GLOB_RECURSE W4_PROTOCOL_INCLUDE protocol/*.hpp)
file(GLOB_RECURSE W4_PROTOCOL_SOURCE protocol/*.cpp)

add_library(w4-protocol)

target_include_directories(w4-protocol
  PUBLIC
    .
  )

target_sources(w4-protocol
  PUBLIC
    ${W4_PROTOCOL_INCLUDE}
  PRIVATE
    ${W4_PROTOCOL_SOURCE}
  )

target_link_libraries(w4-protocol
  PUBLIC
    w4-network  
    w4-stream
  )

############################# stream #############################

file(GLOB_RECURSE W4_STREAM_INCLUDE stream/*.hpp)
file(GLOB_RECURSE W4_STREAM_SOURCE stream/*.cpp)

add_library(w4-stream)

target_include_directories(w4-stream
  PUBLIC
    .
  )

target_sources(w4-stream
  PUBLIC
    ${W4_STREAM_INCLUDE}
  PRIVATE
    ${W4_STREAM_SOURCE}
  )

target_link_libraries(w4-stream
  PUBLIC
    w4-network  
  )

############################# utils #############################

file(GLOB_RECURSE W4_UTILS_INCLUDE utils/*.hpp)
file(GLOB_RECURSE W4_UTILS_SOURCE utils/*.cpp)

add_library(w4-utils)

target_include_directories(w4-utils
  PUBLIC
    .
  )

target_sources(w4-utils
  PUBLIC
    ${W4_UTILS_INCLUDE}
  PRIVATE
    ${W4_UTILS_SOURCE}
  )