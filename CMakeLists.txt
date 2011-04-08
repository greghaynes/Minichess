project(minichess)

set(MINICHESS_SRCS
	main.cpp
	board.cpp
	boardslot.cpp
	boardgenerator.cpp
	player.cpp
	randomplayer.cpp
	game.cpp
	move.cpp
	location.cpp)

add_executable(minichess ${MINICHESS_SRCS})

