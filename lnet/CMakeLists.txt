# LNet for WWIV5
set_max_warnings()

add_executable(lnet lnet.cpp lnet_main.cpp)
target_link_libraries(lnet net_core core sdk local_io localui)

