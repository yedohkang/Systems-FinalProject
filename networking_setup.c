#include "networking.h"

// code credit to Mr. DW
// altered and added a few lines so that it would work with our code

void error_check (int i, char *s) { 
  // modify behavior after testing
  if (i < 0) {
    printf("[%s] error %d: %s\n", s, errno, strerror(errno));
    exit(1);
  }
}

int server_setup (char * address) {
  int sd, i;

  // create the socket
  sd = socket(AF_INET, SOCK_STREAM, 0);
  error_check(sd, "server socket");
  printf("[server] socket created\n");

  // allow reuse of address
  int enable = 1;
  setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int));
  setsockopt(sd, SOL_SOCKET, SO_REUSEPORT, &enable, sizeof(int));

  // setup structs for getaddrinfo
  struct addrinfo * hints, * results;
  hints = (struct addrinfo *)calloc(1, sizeof(struct addrinfo));
  hints->ai_family = AF_INET;  // IPv4 address
  hints->ai_socktype = SOCK_STREAM;  // TCP socket
  hints->ai_flags = AI_PASSIVE;  // Use all valid addresses
  getaddrinfo(address, PORT, hints, &results); // NULL means use local address

  // bind the socket to address and port
  i = bind(sd, results->ai_addr, results->ai_addrlen);
  error_check(i, "server bind");
  printf("[server] socket bound\n");

  // set socket to listen state
  i = listen(sd, 10);
  error_check(i, "server listen");
  printf("[server] socket in listen state\n");

  // free the structs used by getaddrinfo
  free(hints);
  freeaddrinfo(results);
  return sd;
}

int server_connect (int sd) {
  int client_socket;
  socklen_t sock_size;
  struct sockaddr_storage client_address;
  sock_size = sizeof(client_address);

  client_socket = accept(sd,(struct sockaddr *)&client_address, &sock_size);
  error_check(client_socket, "server accept");

  return client_socket;
}

int client_setup (char * server) {
  int sd, i;

  // create the socket
  sd = socket(AF_INET, SOCK_STREAM, 0);
  error_check(sd, "client socket");

  // run getaddrinfo
  // hints->ai_flags not needed because the client
  // specifies the desired address.
  struct addrinfo * hints, * results;
  hints = (struct addrinfo *)calloc(1, sizeof(struct addrinfo));
  hints->ai_family = AF_INET;  // IPv4
  hints->ai_socktype = SOCK_STREAM;  // TCP socket
  getaddrinfo(server, PORT, hints, &results);

  // connect to the server
  // connect will bind the socket for us
  i = connect(sd, results->ai_addr, results->ai_addrlen);
  error_check(i, "client connect");

  free(hints);
  freeaddrinfo(results);

  return sd;
}
