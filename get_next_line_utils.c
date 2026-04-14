/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msobral- <msobral-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 11:10:37 by msobral-          #+#    #+#             */
/*   Updated: 2025/11/18 15:37:09 by msobral-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	clear_buffer(char *buffer)
{
	int	i;

	i = 0;
	while (buffer[i])
		buffer[i++] = 0;
}

size_t	gnl_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0' && s[i] != '\n')
		i++;
	if (s[i] == '\n')
		i++;
	return (i);
}

int	gnl_strchr(char *s, int c)
{
	int	i;
	int	j;
	int	nl;

	i = 0;
	j = 0;
	nl = 0;
	while (s[i])
	{
		if (nl == 1)
		{
			s[j] = s[i];
			j++;
		}
		if (s[i] == (char)c)
			nl = 1;
		s[i] = '\0';
		i++;
	}
	return (nl);
}

char	*gnl_strjoin(char *s1, char *s2)
{
	char	*temp;
	size_t	i;
	size_t	j;

	temp = malloc(sizeof(char) * (gnl_strlen(s1) + gnl_strlen(s2) + 1));
	if (!temp)
		return (free(s1), NULL);
	i = 0;
	j = 0;
	while (s1 && s1[i])
	{
		temp[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		temp[i] = s2[j];
		i++;
		if (s2[j] == '\n')
			break ;
		j++;
	}
	temp[i] = '\0';
	free(s1);
	return (temp);
}
