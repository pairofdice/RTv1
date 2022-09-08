/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 17:00:22 by jsaarine          #+#    #+#             */
/*   Updated: 2022/09/08 19:18:38 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/RTv1.h"

int	handle_args(int argc, char **argv, t_context *ctx)
{
	int	fd;

	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd < 0)
			exit(1);
	}
	else
	{
		ft_putstr("Usage: ./RTv1 <scene>\n");
		exit(1);
	}
	load_scene(fd, ctx);
	close(fd);
	return (1);
}

static void	free_array(void **array)
{
	void	**temp;

	temp = *array;
	while (*temp)
		ft_memdel(temp++);
	free(*array);
	*array = NULL;
}

/* static void	process_object(char **words)
{
	while (*words != 0)
	{
		printf("- %s\n", *words);
		words++;
	}
	printf("Object has been processed\n");
}
 */
float ft_atof(char *str)
{
	float	result;
	int		fraction;
	int		fraction_len;
	float neg;

	neg = 1.0;
	if (!str)
		return 0.0;
	if (*str == '-')
	{
		neg = -1.0;
	}
		printf("\nnegative!\n");
	result = ft_abs(ft_atoi(str));
	str = ft_strchr(str, '.');
	if (!str)
		return 0.0;
	str++;
	fraction = ft_abs(ft_atoi(str));
	fraction_len = ft_nbrlen(fraction);
	result += (float)fraction/pow(10, fraction_len);
	return (result * neg);
}

int	check_triple_length(char **strs)
{
	int	c;

	c = 0;
	while (strs[c] != 0)
		c++;
	if (c != 3)
		return (0);
	return (1);
}

/* static void	process_light()
{
	printf("Light has been processed\n");
} */

t_point read_triple(t_context *ctx, char **strs)
{
	t_point p;

	int	valid;

	valid = 0;

	if (!check_triple_length(++strs))
		close_rtv1(ctx); 
	if (strs[0])
	p.x = ft_atof(strs[0]);
	p.y = ft_atof(strs[1]);
	p.z = ft_atof(strs[2]);
	return (p);
}



static void	process_line(t_context *ctx, char ***words/* , t_vec *obj_vec */)
{
	// t_object	obj;
	int			i;
	// t_point		color;

	i = 0;
	if (!words || !(*words) || !(**words) || !(***words))
		return ;
	**words =   ft_strtrim(**words);
	// printf("\n %s ", **words);

	if (ft_strncmp(**words, "loc", 3) == 0)
		ctx->obj.loc = read_triple(ctx, *words);
	if (ft_strncmp(**words, "color", 5) == 0)
		ctx->obj.color = read_triple(ctx, *words);
	if (ft_strncmp(**words, "size", 4) == 0)
	{
		(*words)++;
		printf("%s", **words);
		ctx->obj.size = ft_atof(**words);
		printf(" - %f", ctx->obj.size);
		
	}
	//printf(" \tType id: %d", ctx->parse_obj.type);
}

int	load_scene(int fd, t_context *ctx)
{
	char	*line;
	char	**words;
	char	**temp;
	//t_vec	obj_vec;

	printf("...\n");
	vec_new(&ctx->scene, BUFF_SIZE * 2, sizeof(t_object));
	while (get_next_line(fd, &line))
	{
		words = ft_strsplit(line, ' ');
		temp = words;
		if (*temp)
		{
			if (ctx->parse_state == NOTHING && **temp == '{')
			{
				ctx->parse_state = PROCESSING;
				check_type(temp, ctx);
				//vec_new(&obj_vec, ft_strlen(line) / 2 + 1, sizeof(t_object));
			}
			else if (**temp == '}')
			{
				// printf("Hello\n");
				ctx->parse_state = NOTHING;
				//push_obj(ctx);
				vec_push(&ctx->scene, &ctx->obj);
			}
			else if (ctx->parse_state == PROCESSING)
			{
				process_line(ctx, &words/* , &obj_vec  */);
			}
		}
		free_array((void *)&temp);
		ft_strdel(&line);
	}
	return (1);
}
