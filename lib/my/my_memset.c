/*
** memset.c for Rush03 in /home/rajiska/Epitech/CPool_rush3/src
** 
** Made by Corlouer Doriann
** Login   <corlouer_d@epitech.net>
** 
** Started on  Sat Oct 29 22:02:14 2016 Corlouer Doriann
** Last update Mon Jan 30 10:19:00 2017 Corlouer Doriann
*/

void	my_memset(char *s, char c, int len)
{
  int	it;

  it = 0;
  while (it < len)
    {
      *(s + it) = c;
      it++;
    }
}
