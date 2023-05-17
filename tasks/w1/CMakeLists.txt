# -------------------- network --------------------

file(GLOB_RECURSE INFRA_INCLUDE infra/*.hpp)
file(GLOB_RECURSE INFRA_SOURCE infra/*.cpp)


file(GLOB_RECURSE NETWORK_INCLUDE network/*.hpp)
file(GLOB_RECURSE NETWORK_SOURCE network/*.cpp)

# -------------------- client --------------------

set(CLIENT_SOURCE client.cpp)

add_executable(w1-client)

target_include_directories(w1-client
  PUBLIC
    .
  )

target_sources(w1-client
  PUBLIC
    ${INFRA_INCLUDE}
    ${NETWORK_INCLUDE}
  PRIVATE
    ${INFRA_SOURCE}
    ${NETWORK_SOURCE}
    ${CLIENT_SOURCE}
  )

# -------------------- server --------------------

set(SERVER_SOURCE server.cpp)

add_executable(w1-server)

target_include_directories(w1-server
  PUBLIC
    .
  )

target_sources(w1-server
  PUBLIC
    ${INFRA_INCLUDE}
    ${NETWORK_INCLUDE}
  PRIVATE
    ${INFRA_SOURCE}
    ${NETWORK_SOURCE}
    ${SERVER_SOURCE}
  )