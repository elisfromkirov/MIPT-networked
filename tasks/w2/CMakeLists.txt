############################# client #############################

file (GLOB_RECURSE W2_CLIENT_INCLUDE client/*.hpp)
file (GLOB_RECURSE W2_CLIENT_SOURCE client/*.cpp)

add_executable(w2-client)

target_include_directories(w2-client
  PUBLIC
    .
  )

target_sources(w2-client
  PUBLIC
    ${W2_CLIENT_INCLUDE}
  PRIVATE
    ${W2_CLIENT_SOURCE}
  )

target_link_libraries(w2-client
  PUBLIC
    w2-network
    w2-protocol
    w2-input
  )

############################# game #############################

file (GLOB_RECURSE W2_SERVER_INCLUDE game/*.hpp)
file (GLOB_RECURSE W2_SERVER_SOURCE game/*.cpp)

add_executable(w2-server)

target_include_directories(w2-server
  PUBLIC
    .
  )

target_sources(w2-server
  PUBLIC
    ${W2_SERVER_INCLUDE}
  PRIVATE
    ${W2_SERVER_SOURCE}
  )

target_link_libraries(w2-server
  PUBLIC
    w2-network
    w2-protocol
  )

############################# lobby #############################

file (GLOB_RECURSE W2_LOBBY_INCLUDE lobby/*.hpp)
file (GLOB_RECURSE W2_LOBBY_SOURCE lobby/*.cpp)

add_executable(w2-lobby)

target_include_directories(w2-lobby
  PUBLIC
    .
  )

target_sources(w2-lobby
  PUBLIC
    ${W2_LOBBY_INCLUDE}
  PRIVATE
    ${W2_LOBBY_SOURCE}
  )

target_link_libraries(w2-lobby
  PUBLIC
    w2-network
    w2-protocol
  )

############################# input #############################

file(GLOB_RECURSE W2_INPUT_INCLUDE input/*.hpp)
file(GLOB_RECURSE W2_INPUT_SOURCE input/*.cpp)

add_library(w2-input)

target_include_directories(w2-input
  PUBLIC
    .
  )

target_sources(w2-input
  PUBLIC
    ${W2_INPUT_INCLUDE}
  PRIVATE
    ${W2_INPUT_SOURCE}
  )

############################# network #############################

file(GLOB_RECURSE W2_NETWORK_INCLUDE network/*.hpp)
file(GLOB_RECURSE W2_NETWORK_SOURCE network/*.cpp)

add_library(w2-network)

target_include_directories(w2-network
  PUBLIC
    .
    ${MULTIPLAYER_SOURCE_DIR}/third_party/enet/include
  )

target_sources(w2-network
  PUBLIC
    ${W2_NETWORK_INCLUDE}
  PRIVATE
    ${W2_NETWORK_SOURCE}
  )

target_link_libraries(w2-network
  PUBLIC
    enet
  )

############################# protocol #############################

file(GLOB_RECURSE W2_PROTOCOL_INCLUDE protocol/*.hpp)
file(GLOB_RECURSE W2_PROTOCOL_SOURCE protocol/*.cpp)

add_library(w2-protocol)

target_include_directories(w2-protocol
  PUBLIC
    .
  )

target_sources(w2-protocol
  PUBLIC
    ${W2_PROTOCOL_INCLUDE}
  PRIVATE
    ${W2_PROTOCOL_SOURCE}
  )