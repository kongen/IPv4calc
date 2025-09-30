add_executable(ipv4calc main.cpp)

install(TARGETS ipv4calc
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
