# Project Needs a name ofcourse
project(plasma-narGarTagetHemlasmoid)

# Find the required Libaries
find_package(KDE4 REQUIRED)
include(KDE4Defaults)

find_package(Qt4 4.7.2 REQUIRED)
SET(QT_USE_QTNETWORK TRUE)
add_definitions (${QT_DEFINITIONS} ${KDE4_DEFINITIONS})
include_directories(
   ${CMAKE_SOURCE_DIR}
   ${CMAKE_BINARY_DIR}
   ${KDE4_INCLUDES}
   )
 
# We add our source code here
set(narGarTagetHemPlasmoid_SRCS narGarTagetHemPlasmoid.cpp)
 
# Now make sure all files get to the right place
kde4_add_plugin(plasma_applet_narGarTagetHemPlasmoid ${narGarTagetHemPlasmoid_SRCS})
target_link_libraries(plasma_applet_narGarTagetHemPlasmoid
                      ${QT_QTNETWORK_LIBRARY}
                      ${KDE4_PLASMA_LIBS} ${KDE4_KDEUI_LIBS})
 
install(TARGETS plasma_applet_narGarTagetHemPlasmoid
        DESTINATION ${PLUGIN_INSTALL_DIR})
 
install(FILES plasma-applet-narGarTagetHemPlasmoid.desktop
        DESTINATION ${SERVICES_INSTALL_DIR})
