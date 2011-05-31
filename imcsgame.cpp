#include "imcsgame.h"
#include "smartplayer.h"
#include "boardgenerator.h"

#include <iostream>

#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

#define IMCS_HOSTNAME "svcs.cs.pdx.edu"
#define IMCS_PORT "3589"

ImcsGame::ImcsGame(void)
{
	m_valid_conn = false;
	m_player = 0;
	struct addrinfo *ai;
	struct addrinfo hints;

	if((m_sock_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("Creating socket for imcs");
		return;
	}

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_family = AF_INET;
	hints.ai_canonname = 0;

	if(getaddrinfo(IMCS_HOSTNAME, IMCS_PORT, &hints, &ai) == -1) {
		perror("Getting addr info for hostname");
		return;
	}

	if(connect(m_sock_fd, ai->ai_addr, sizeof(struct sockaddr)) == -1) {
		perror("Connecting to imcs server");
		return;
	}

	m_valid_conn = true;
	m_sock_ffd = fdopen(m_sock_fd, "r+");
}

ImcsGame::~ImcsGame(void)
{
	if(m_sock_fd > 0)
	{
		close(m_sock_fd);
		fclose(m_sock_ffd);
	}

	if(m_player)
		delete m_player;
}

void ImcsGame::setPlayer(Player *p)
{
	if(m_player)
		delete m_player;
	m_player = p;
}

#define SAFE_FREE(x) if(x) free(x);
#define DO_RETURN SAFE_FREE(buff)\
                     return;

void ImcsGame::play(const char *username, const char *pass, char piece)
{
	char *buff = 0;
	char buff_2[512];
	char *itr, *end;
	size_t len = 0;
	int game_id;

	if(getline(&buff, &len, m_sock_ffd) == -1) {
		perror("Reading from imcs");
		DO_RETURN
	}

	if(strncmp("100 imcs 2.5", buff, 12)) {
		fprintf(stderr, "Non IMCS or incorrect IMCS version. Received %s", buff);
		DO_RETURN
	}
	printf("Connected to valid IMCS\n");

	printf("Logging in...");
	fflush(stdout);
	sprintf(buff, "me %s %s\n", username, pass);
	if(write(m_sock_fd, buff, strlen(buff)) == -1) {
		perror("Sending login request");
		DO_RETURN
	}

	if(getline(&buff, &len, m_sock_ffd) == -1) {
		perror("Reading from imcs after me request");
		DO_RETURN
	}

	sprintf(buff_2, "201 hello %s", username);
	if(strncmp(buff_2, buff, strlen(buff_2))) {
		fprintf(stderr, "Invalid login");
		DO_RETURN
	}
	printf("Login success\n");

	if(!m_player) {
		// Try to join an available game
		sprintf(buff, "list\n");
		if(write(m_sock_fd, buff, strlen(buff)) == -1) {
			perror("Listing available games");
			DO_RETURN
		}

		if(getline(&buff, &len, m_sock_ffd) == -1) {
			perror("Reading from imcs after list request");
			DO_RETURN
		}

		if(getline(&buff, &len, m_sock_ffd) == -1) {
			perror("Reading from imcs second time after list request");
			DO_RETURN
		}
		while(buff[0] != '.') {
			// Dont try to join in progress game
			if(!strstr(buff, "offer")) {
				if(getline(&buff, &len, m_sock_ffd) == -1) {
					perror("Reading from imcs second time after list request");
					DO_RETURN
				}
				continue;
			}

			sscanf(buff, " %d", &game_id);
			printf("Found game %d, accepting\n", game_id);
			sprintf(buff_2, "accept %d\n", game_id);

			do {
				if(getline(&buff, &len, m_sock_ffd) == -1) {
					perror("Reading from imcs in loop after list request");
					DO_RETURN
				}
			} while(buff[0] != '.');
			
			if(write(m_sock_fd, buff_2, strlen(buff_2)) == -1) {
				perror("Sending accept request");
				DO_RETURN
			}

			startPlaying();
			DO_RETURN
		}
		printf("No available games found.\n");
	}
	
	printf("Offering game\n");
	sprintf(buff, "offer %c\n", piece);
	if(write(m_sock_fd, buff, strlen(buff)) == -1) {
		perror("Sending offer request");
		DO_RETURN
	}

	startPlaying();
	DO_RETURN
}

#undef DO_RETURN
#define DO_RETURN SAFE_FREE(buff)\
                  SAFE_FREE(p)\
                  SAFE_FREE(b)\
                  return;

void ImcsGame::startPlaying(void)
{
	char *buff = 0;
	char *itr, *end;
	int game_id;
	size_t len;
	float w_min, w_sec, b_min, b_sec;
	int move_num;
	char color;
	Player *p = 0;
	Board *b = 0;
	bool my_move = false;

	printf("Waiting for game acceptance...\n");

	if(getline(&buff, &len, m_sock_ffd) == -1) {
                perror("Reading from imcs on game start");
		DO_RETURN
        }
	
	if(EOF == sscanf(buff, "%d %c %f:%f %f:%f", &game_id, &color, &w_min, &w_sec, &b_min, &b_sec)) {
		perror("Parsing game accepted id string");
		DO_RETURN
	}

	printf("Accepted, playing game id %d\n", game_id);

	switch(color) {
		case 'W':
			p = new SmartPlayer(Player::Player1);
			my_move = true;
			break;
		case 'B':
			p = new SmartPlayer(Player::Player2);
			my_move = false;
			break;
		default:
			fprintf(stderr, "Could not parse game acept string, got %s\n", buff);
			DO_RETURN
	}

	char move_color;
	char board[37];
	int board_ndx;
	std::string *str;
	struct timeval time;
	Move mv;
	// Main game loop
	do {
		// Kill leading blank line
		do {
			if(getline(&buff, &len, m_sock_ffd) == -1) {
				printf("Reading move leading blank line\ngot: %s", buff);
				DO_RETURN
			}
		} while(!isspace(buff[0]));

		
		// Read in move num / color line
		if(getline(&buff, &len, m_sock_ffd) == -1) {
			perror("Reading move info line");
			DO_RETURN
		}
		sscanf(buff, "%d %c", &move_num, &move_color);

		// Read in board
		board_ndx = 0;
		do {
			if(getline(&buff, &len, m_sock_ffd) == -1) {
				fprintf(stderr, "Reading move leading blank line");
				fprintf(stderr, "Got %s\n", buff);
				DO_RETURN
			}

			if(board_ndx < 36) {
				strncpy(&board[board_ndx], buff, 5);
				board_ndx += 5;
				board[board_ndx] = '\n';
				board_ndx++;
				board[board_ndx] = '\0';
			}
		} while(!isspace(buff[0]));
		if(board_ndx != 36) {
			fprintf(stderr, "Did not read in valid board.\n");
			DO_RETURN
		}

		b = BoardGenerator::fromString(board);

		printf("Move: %d\n", move_num);
		str = b->toString();
		printf("%s\n", str->c_str());
		delete str;

		if(getline(&buff, &len, m_sock_ffd) == -1) {
			perror("Reading move / time line");
			DO_RETURN
		}

		sscanf(buff, "? %f:%f %f:%f", &w_min, &w_sec, &b_min, &b_sec);
		if(color == 'W')
			time.tv_sec = (w_min * 60) + w_sec;
		else
			time.tv_sec = (b_min * 60) + b_sec;

		printf("%f:%f %f:%f\n", w_min, w_sec, b_min, b_sec);
		mv = p->move(b, &time, move_num);
		sprintf(buff, "%c%c-%c%c\n", (char)('a'+mv.from().x()), (char)('6'-mv.from().y()),
		                             (char)('a'+mv.to().x()), (char)('6'-mv.to().y()));
		printf("%s\n", buff);
		b->move(mv);
		printf("Move: %d\n", move_num);
		str = b->toString();
		printf("%s\n", str->c_str());
		delete str;
		
		if(write(m_sock_fd, buff, strlen(buff)) == -1) {
			perror("Sending move");
			DO_RETURN
		}

		delete b;
		b = 0;

		if(getline(&buff, &len, m_sock_ffd) == -1) {
			perror("reading opponent move");
			DO_RETURN
		}

	} while(buff[0] != '-' && strncmp(buff, "232", 3) && strncmp(buff, "231", 3));
	// End main game loop

	printf("%s\n", buff);
	if(!strncmp(buff, "232", 3)) {
		if(color == 'B') {
			printf("You win!\n");
		} else {
			printf("You lose!\n");
		}
	} else if(!strncmp(buff, "231", 3)) {
		if(color == 'W') {
			printf("You win!\n");
		} else {
			printf("You lose!\n");
		}
	} else {
		fprintf(stderr, "Game ended due to error condition.\n");
		fprintf(stderr, "error line was %s\n", buff);
	}
}

#undef DO_RETURN
#undef SAFE_FREE

