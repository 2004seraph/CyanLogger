SET(
    APP_EXE basicTestApp
)

ADD_EXECUTABLE(
    ${APP_EXE}
    main.cpp
)

target_include_directories(
    ${APP_EXE} 
    PRIVATE 
    ${SOURCE_SUBDIR}
)

TARGET_LINK_LIBRARIES(
    ${APP_EXE} 
    CyanLogger
)

add_test(
    NAME basicTestApp
    COMMAND basicTestApp
)