# Build as object library
set(ECALUDP_LIBRARY_TYPE OBJECT)

# Add udpcap library from subdirectory. Use the inner lib-only directory, as we don't need the test, samples, etc.
add_subdirectory(thirdparty/ecaludp/ecaludp/ecaludp EXCLUDE_FROM_ALL)
add_library(ecaludp::ecaludp ALIAS ecaludp)

# move the udpcap target to a subdirectory in the IDE
set_property(TARGET ecaludp PROPERTY FOLDER lib/ecaludp)

list(PREPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/Modules)