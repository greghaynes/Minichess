project(minichess)

set(MINICHESS_SRCS
	main.cpp
	board.cpp
	boardslot.cpp
	location.cpp)

add_executable(minichess ${MINICHESS_SRCS})

