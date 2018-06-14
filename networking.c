#include "networking.h"

// code credit for networking.h to Mr. DW

int player (int argc, char ** argv) {
	// PARAMETERS player 1 should run with cmd line arg "1"
	// player 2 should run with cmd line arg "2" and player 1's IP address
	// RETURNS 1 for player 1 ("server")
	// 2 for player 2 ("client")
	// exits if error
	
	if (argc >= 2) {
		if (!strcmp(argv[1], "1")) {
			return 1;
		} 
		else if (!strcmp(argv[1], "2")) {
			if (argc >= 3) {
				return 2;
			} 
			else{
				printf("specify player 1's IP address\n");
				exit(1);
			}
		} 
		else{
			printf("invalid command line arguments\n");
			exit(1);
		}
	} 
	else {
		printf("insufficient command line arguments\n");
		exit(1);
	}
	return 0;
}

// return if successfully connected
// handshake
int connecting (int player, char * address, int * listen_socket_p, int * client_socket_p, int * server_socket_p) { 
	if (player == 1) {
		// server code
		*listen_socket_p = server_setup(address);
		*client_socket_p = server_connect(*listen_socket_p);

	} 
	else {
		// client code
		// int server_socket = client_setup(address);
		*server_socket_p = client_setup(address);
	}
	return 1;
}
