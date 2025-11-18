include(FetchContent)
function(GetRemoteURL)
    cmake_parse_arguments(REMOTE "" "NAME;VERSION;URL;PARENT_DIR;OUTPUT_DIR" "" ${ARGN})
    set(REMOTE_DESTINATION ${REMOTE_PARENT_DIR}/${REMOTE_NAME})
    FetchContent_Declare(
        ${REMOTE_NAME}
        URL                 ${REMOTE_URL}
        FIND_PACKAGE_ARGS   ${REMOTE_VERSION}
        SOURCE_DIR          ${REMOTE_DESTINATION}
    )
    FetchContent_MakeAvailable(${REMOTE_NAME})

    set("${REMOTE_NAME}_LOCATION" ${REMOTE_DESTINATION} PARENT_SCOPE)
endfunction()

function(GetRemoteTag)
    cmake_parse_arguments(REMOTE "" "NAME;PARENT_DIR;REPO;TAG" "" ${ARGN})
    set(REMOTE_DESTINATION ${REMOTE_PARENT_DIR}/${REMOTE_NAME})
    FetchContent_Declare(
        ${REMOTE_NAME}
        SOURCE_DIR          ${REMOTE_DESTINATION}
        GIT_REPOSITORY      ${REMOTE_REPO}
        GIT_TAG             ${REMOTE_TAG}
    )
    FetchContent_MakeAvailable(${REMOTE_NAME})

    set("${REMOTE_NAME}_LOCATION" ${REMOTE_DESTINATION} PARENT_SCOPE)
endfunction()
