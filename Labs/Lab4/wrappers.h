
#ifndef WRAPPERS_H
#define WRAPPERS_H

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <errno.h>

pid_t Fork(void);

int Pipe(int *pipefd);

int Read(int fd, char *buf, size_t count);

ssize_t Write(int fd, const void *buf, size_t count);

pid_t Wait(int *status);

pid_t Waitpid(pid_t pid, int *status, int option);

int Open(const char *pathname, int flags, mode_t mode);

int Close(int fd);

ssize_t Write(int fd, const void *buf, size_t count);

int Connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

int Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

int Listen(int sockfd, int backlog);

int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);


#endif
