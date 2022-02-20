/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmickey <hmickey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 18:39:14 by lignigno          #+#    #+#             */
/*   Updated: 2022/02/20 05:35:23 by hmickey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "header.hpp"
#include <sstream>

#define _PRINT_HEADER

static bool	get_msg(std::string &msg)
{
	std::getline(std::cin, msg, '\n');
	if (msg.length() == 0)
		msg = "empty message";
	if (std::cin.eof())
		return false;
	return true;
}

int main(int count, char **values)
{
	std::cout << "\nCLIENT START\n\n";
	struct sockaddr_in sa;
	std::stringstream ss;
	int res;
	int SocketFD;

	ss << IP_ADRESS;
	SocketFD = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (SocketFD == -1)
	{
		perror("cannot create socket");
		exit(EXIT_FAILURE);
	}

	memset(&sa, 0, sizeof sa);

	sa.sin_family = AF_INET;
	sa.sin_port = htons(PORT);
	res = inet_pton(AF_INET, ss.str().c_str(), &sa.sin_addr);

		if (connect(SocketFD, (struct sockaddr *)&sa, sizeof(sa)) == -1)
		{
			perror("connect failed");
			close(SocketFD);
			exit(EXIT_FAILURE);
		}

	while (1)
	{
		char	*buff = new char[BUFF_SIZE];
		int		readed;


		std::cout << COL_Y << "enter message or exit" << COL_RES << "\n";
		std::string msg;

		if (!get_msg(msg))
		{
			close(SocketFD);
			std::cout << "\nCLIENT GOT EOF\n\n";
			exit (0);
		}
		if (msg == "EXIT")
		{
			break ;
		}
		write(SocketFD, msg.c_str(), msg.length());
		readed = read(SocketFD, buff, BUFF_SIZE);
		buff[readed] = '\0';
		printf("server: %s\n", buff);
	}
	std::cout << "\nCLIENT FINISH\n\n";
	close(SocketFD);
	return EXIT_SUCCESS;
}
