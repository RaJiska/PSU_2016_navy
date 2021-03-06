/*
** main.c for navy in /home/rajiska/Epitech/PSU_2016_navy/src
** 
** Made by Corlouer Doriann
** Login   <corlouer_d@epitech.net>
** 
** Started on  Mon Jan 30 09:38:07 2017 Corlouer Doriann
** Last update Fri Feb  3 16:22:07 2017 Corlouer Doriann
*/

#include "../include/navy.h"

static int	exit_on_err(int fd, t_map *p1, t_map *p2, const char *s)
{
  my_putstr_err(s);
  if (fd > (-1))
    close(fd);
  if (p1 != NULL)
    map_destroy(&p1);
  if (p2 != NULL)
    map_destroy(&p2);
  return 84;
}

static int	needs_help(int argc, char **argv)
{
  int		it;

  it = 1;
  while (it < argc)
    {
      if (my_strcmp(argv[it], "-h") == 0)
	{
	  my_printf("USAGE\n\t%s [address[:port]] navy_positions\n", argv[0]);
	  my_printf("DESCRIPTION\n\tfirst_player_pid\tonly for the 2nd player.");
	  my_printf(" pid of the first player.\n\tnavy_positions\t\t");
	  my_printf("file representing the positions of the ships.\n");
	  return TRUE;
	}
      it++;
    }
  return FALSE;
}

int	main(int argc, char **argv)
{
  int	fd;
  t_map	*p1;
  t_map	*p2;
  int	ret;
  char	**wt;

  if (argc > 3 || argc < 2)
    return (exit_on_err((-1), NULL, NULL, "Arg Error.\n"));
  if (needs_help(argc, argv))
    return 0;
  if ((fd = open(((argc == 3) ? argv[2] : argv[1]), O_RDONLY)) < 0)
    return (exit_on_err(fd, NULL, NULL, "Could not open map.\n"));
  p1 = map_create(fd, ((argc == 2) ? 1 : 2));
  p2 = map_create((-1), ((argc == 3) ? 1 : 2));
  if (p1 == NULL || p2 == NULL)
    return (exit_on_err(fd, p1, p2, "Map format/creation failure\n"));
  wt = my_strsplit(argv[1], ":");
  ret = navy(p1, p2, ((argc == 3) ? wt[0] : NULL),
	     ((wt[1] != 0) ? my_getnbr(wt[1]) : NAVY_NET_PORT));
  my_wordtab_free(wt);
  map_destroy(&p1);
  map_destroy(&p2);
  close(fd);
  return ret;
}
