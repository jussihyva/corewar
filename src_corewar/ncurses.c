/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakala <jhakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 20:11:51 by jhakala           #+#    #+#             */
/*   Updated: 2020/08/17 17:29:32 by jhakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	highlight_c(t_game *game)
{
	t_carriage	*c;
	int			row;
	int			cap;

	c = game->c_lst;
	while (c)
	{
		row = ft_place(c->place) / 64;
		cap = ft_place(c->place) % 64;
		attron(COLOR_PAIR(c->owner + 4));
		mvprintw(row, 9 + cap * 3, "%02x",
				(unsigned char)game->arena[ft_place(c->place)]);
		attroff(COLOR_PAIR(c->owner + 4));
		c = c->next;
	}
}

void	print_ncurses_end(t_mem *mem)
{
	int id;
	int end;

	end = 1;
	id = mem->game->last_alive->id;
	mvprintw(mem->n_player * 2 + 3, 205, "WINNER: ");
	attron(COLOR_PAIR(id));
	mvprintw(mem->n_player * 2 + 3, 213, "%s",
			mem->game->last_alive->header->prog_name);
	attroff(COLOR_PAIR(id));
	while (end == 1)
	{
		if (getch() == 27)
			end = 0;
	}
}

void	hex_mem(char *arena, t_mem *mem)
{
	int i;
	int row;
	int cap;

	i = 0;
	row = 0;
	cap = 1;
	mvprintw(0, 0, "0x%04x : ", i);
	attron(COLOR_PAIR(mem->game->owner[i]));
	mvprintw(0, 9, "%02x ", (unsigned char)arena[i++]);
	while (i < MEM_SIZE)
	{
		attroff(COLOR_PAIR(mem->game->owner[i - 1]));
		if (i % mem->dump_type == 0)
		{
			row++;
			mvprintw(row, 0, "0x%04x : ", i);
			cap = 0;
		}
		attron(COLOR_PAIR(mem->game->owner[i]));
		mvprintw(row, 9 + cap * 3, "%02x ", (unsigned char)arena[i++]);
		cap++;
	}
	attroff(COLOR_PAIR(mem->game->owner[i - 1]));
}

void	inputs(t_mem *mem)
{
	int input;

	input = getch();
	if (input != -1)
	{
		mem->last_key = input;
		mvprintw(68, 12, "lastkey pressed = %d", mem->last_key);
		refresh();
	}
	if (input == 32)
		mem->pause = mem->pause == 0 ? 1 : 0;
	else if (input == 109 && mem->speed < 512)
		mem->speed *= 2;
	else if (input == 110 && mem->speed > 1)
		mem->speed /= 2;
	else if (input == 27)
	{
		endwin();
		if (mem->leaks == 1)
			system("leaks corewar");
		exit(0);
	}
	mvprintw(17, 205, "speed =     ");
	mvprintw(17, 205, "speed = %d", mem->speed);
	mvprintw(15, 205, "cycle = %d", mem->game->total_cycles);
}

void	print_ncurses_arena(char *arena, t_mem *mem)
{
	int		wait;

	hex_mem(arena, mem);
	highlight_c(mem->game);
	inputs(mem);
	mvprintw(17, 225, "n -/+ m");
	mvprintw(15, 225, "space toggle pause");
	while (mem->pause == 1)
		inputs(mem);
	wait = 1000 / mem->speed;
	if (wait > 0)
		timeout(wait);
	move(0, 0);
	refresh();
}
