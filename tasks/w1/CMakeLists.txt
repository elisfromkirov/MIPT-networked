# -------------------- common --------------------

file(GLOB_RECURSE INFRA_INCLUDE infra/*.hpp)
file(GLOB_RECURSE INFRA_SOURCE infra/*.cpp)

file(GLOB_RECURSE NETWORK_INCLUDE network/*.hpp)
file(GLOB_RECURSE NETWORK_SOURCE network/*.cpp)

file(GLOB_RECURSE PROTOCOL_INCLUDE protocol/*.hpp)
file(GLOB_RECURSE PROTOCOL_SOURCE protocol/*.cpp)

# -------------------- client --------------------

file(GLOB_RECURSE CLIENT_INCLUDE client/*.hpp)
file(GLOB_RECURSE CLIENT_SOURCE client/*.cpp)

add_executable(w1-client)

target_include_directories(w1-client
  PUBLIC
    .
  )

target_sources(w1-client
  PUBLIC
    ${CLIENT_INCLUDE}
    ${INFRA_INCLUDE}
    ${NETWORK_INCLUDE}
    ${PROTOCOL_INCLUDE}
  PRIVATE
    ${CLIENT_SOURCE}
    ${INFRA_SOURCE}
    ${NETWORK_SOURCE}
    ${PROTOCOL_SOURCE}
  )

# -------------------- server --------------------

file(GLOB_RECURSE SERVER_INCLUDE server/*.hpp)
file(GLOB_RECURSE SERVER_SOURCE server/*.cpp)

add_executable(w1-server)

target_include_directories(w1-server
  PUBLIC
    .
  )

target_sources(w1-server
  PUBLIC
    ${CLIENT_INCLUDE}
    ${INFRA_INCLUDE}
    ${NETWORK_INCLUDE}
    ${SERVER_INCLUDE}
  PRIVATE
    ${INFRA_SOURCE}
    ${NETWORK_SOURCE}
    ${PROTOCOL_SOURCE}
    ${SERVER_SOURCE}
  )