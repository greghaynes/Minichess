project(minichess)

set(MINICHESS_SRCS
	main.cpp
	board.cpp
	boardslot.cpp
	boardgenerator.cpp
	player.cpp
	randomplayer.cpp
	smartplayer.cpp
	humanplayer.cpp
	game.cpp
	imcsgame.cpp
	move.cpp
	location.cpp
	zobrist.cpp
	transposetable.cpp)

add_executable(minichess ${MINICHESS_SRCS})

