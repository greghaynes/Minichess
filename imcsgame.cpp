#include "imcsgame.h"

#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
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
}

ImcsGame::~ImcsGame(void)
{
	if(m_sock_fd > 0)
		close(m_sock_fd);

	if(m_player)
		delete m_player;
}

void ImcsGame::setPlayer(Player *p)
{
	if(m_player)
		delete m_player;
	m_player = p;
}

void ImcsGame::play(const char *username, const char *pass, char piece)
{
	char buff[512];
	char buff_2[512];
	char *itr, *end;
	int len;

	if(read(m_sock_fd, buff, 511) == -1) {
		perror("Reading from imcs");
		return;
	}

	if(strncmp("100 imcs 2.5", buff, 12)) {
		fprintf(stderr, "Non IMCS or incorrect IMCS version. Received %s", buff);
		return;
	}
	printf("Connected to valid IMCS\n");

	printf("Logging in...");
	fflush(stdout);
	sprintf(buff, "me %s %s\n", username, pass);
	if(write(m_sock_fd, buff, strlen(buff)) == -1) {
		perror("Sending login request");
		return;
	}

	if(read(m_sock_fd, buff, 511) == -1) {
		perror("Reading from imcs after me request");
		return;
	}

	sprintf(buff_2, "201 hello %s", username);
	if(strncmp(buff_2, buff, strlen(buff_2))) {
		fprintf(stderr, "Invalid login");
		return;
	}
	printf("Login success\n");

	// Try to join an available game
	sprintf(buff, "list\n");
	if(write(m_sock_fd, buff, strlen(buff)) == -1) {
		perror("Listing available games");
		return;
	}

	len = 0;
	do {
		len += read(m_sock_fd, &buff[len], 511);
		if(len == -1) {
			perror("Reading from imcs after list request");
			return;
		}
	} while(!strstr(buff, "\n."));
	buff[len] = '\0';

	if(strncmp(buff, "211", 3)) {
		fprintf(stderr, "Invalid game list response\n");
		return;
	}

	itr = buff;
	while(*itr && *itr != '\n') ++itr;
	if(!*itr || !*(++itr)) {
		fprintf(stderr, "Shouldnt be here...\n");
		return;
	}
	if(*itr == ' ') {
		++itr;
		end = itr;
		while(*end && *end != ' ') ++end;
		*end = '\0';

		printf("Found game %s, accepting\n", itr);
		sprintf(buff, "accept %s\n", itr);
		
		if(write(m_sock_fd, buff, strlen(buff)) == -1) {
			perror("Sending accept request");
			return;
		}

		startPlaying();

		return;
	}

	printf("No valid games found\n");
	
	printf("Offering game\n");
	sprintf(buff, "offer %c\n", piece);
	if(write(m_sock_fd, buff, strlen(buff)) == -1) {
		perror("Sending offer request");
		return;
	}

	if(read(m_sock_fd, buff, 511) == -1) {
		perror("Reading from imcs after offer request");
		return;
	}

	strcpy(buff_2, "103");
	if(strncmp(buff_2, buff, strlen(buff_2))) {
		fprintf(stderr, "Invalid offer acceptance, received: %s\n", buff);
		return;
	}
	
	startPlaying();
}

void ImcsGame::startPlaying(void)
{
	char buff[512];

	printf("Waiting for game acceptance...\n");
	
}

