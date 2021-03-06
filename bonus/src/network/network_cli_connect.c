/*
** network_cli_connect.c for navy in /home/PSU_2016_navy/bonus/src/network
** 
** Made by Corlouer Doriann
** Login   <corlouer_d@epitech.net>
** 
** Started on  Thu Feb  2 16:09:20 2017 Corlouer Doriann
** Last update Sun Feb  5 16:36:25 2017 Corlouer Doriann
*/

#include "../../include/navy.h"

static int	exit_on_err(const char *title)
{
  my_putstr_err(title);
  my_putstr_err(": ");
#ifndef EPITECH_WINDOWS
  my_putstr_err(strerror(errno));
#else
  fprintf(stderr, "%d", WSAGetLastError());
#endif
  my_putchar('\n');
  return FALSE;
}

#ifndef EPITECH_WINDOWS
int	network_cli_connect(t_network *net, const char *addr, int port)
{
  memset(&net->srv, 0, sizeof(t_sockaddr));
  net->srv.sin_family = AF_INET;
  net->srv.sin_port = htons(port);
  net->srv_sck = socket(AF_INET, SOCK_STREAM, 0);
  if (inet_pton(AF_INET, addr, &net->srv.sin_addr) <= 0)
    return (exit_on_err("Network Error"));
  if (connect(net->srv_sck,
	      (struct sockaddr *)&net->srv,
	      sizeof(t_sockaddr)) < 0)
    return (exit_on_err("Network Error"));
  return TRUE;
}
#else
int	network_cli_connect(t_network *net, const char *addr, int port)
{
  if (WSAStartup(MAKEWORD(2, 2), &net->wsadata) != 0)
    return (exit_on_err("ANetwork Error"));
  memset(&net->srv, 0, sizeof(t_sockaddr));
  net->srv_sck = socket(AF_INET, SOCK_STREAM, 0);
  net->srv.sin_family = AF_INET;
  net->srv.sin_addr.s_addr = inet_addr(addr);
  net->srv.sin_port = htons(port);
  if (connect(net->srv_sck,
	      (struct sockaddr *) &net->srv,
	      sizeof(t_sockaddr)) < 0)
    return (exit_on_err("Network Error"));
  return TRUE;
}
#endif
