/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasubuc  <mmasubuc@student.42tokyo.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 01:29:01 by mmasubuc          #+#    #+#             */
/*   Updated: 2022/04/28 17:56:12 by mmasubuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <limits.h>
# include <sys/time.h>

int		ft_atoi(char *str, int *overflow);
size_t	ft_strlen(const char *s);
int		ft_isdigit(int c);
bool	is_digit(char **argv, int i);
long	get_usec(void);
void	sleep_loop_usec(unsigned int need_to_sleep_usec, long past_time_usec);

#endif
