add_executable(goReader ${PROJECT_SOURCE_DIR}/run/main.cpp
                        ${PROJECT_SOURCE_DIR}/src/Configuration.cpp
                        ${PROJECT_SOURCE_DIR}/src/Event.cpp
                        ${PROJECT_SOURCE_DIR}/src/Hit.cpp
                        ${PROJECT_SOURCE_DIR}/src/HitCollection.cpp
                        ${PROJECT_SOURCE_DIR}/src/Map.cpp
                        ${PROJECT_SOURCE_DIR}/src/Reader.cpp)

target_link_libraries(goReader ${ROOT_LIBRARIES})

install(TARGETS goReader
        RUNTIME DESTINATION ${PACKAGE_INSTALL_BIN_DIR})
