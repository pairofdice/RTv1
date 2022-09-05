/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 17:00:22 by jsaarine          #+#    #+#             */
/*   Updated: 2022/09/05 19:50:18 by jsaarine         ###   ########.fr       */
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

static void	process_object(char **words)
{
	while (*words != 0)
	{
		printf("- %s\n", *words);
		words++;
	}
	printf("Object has been processed\n");
}

static void	process_light()
{
	printf("Light has been processed\n");
}

t_point read_triple(char **strs)
{
	t_point p;

	p.x = 0.1;
	p.y = 2.3;
	p.z = 4.5;
	//(*strs)++;
			(strs)++;
			printf("\t %s ", *strs);
			(strs)++;
			printf("\t %s ", *strs);
			(strs)++;
			printf("\t %s ", *strs);
}



 static void	process_line(t_context *ctx, char ***words, t_vec *obj_vec)
{
	t_object	obj;
	int			i;

	i = 0;
	if (ctx->parse_state == PROCESSING && ctx->parse_obj.type == NOTHING)
	{
		// figure out what we're processing and set state
		printf("Processing: -%s-\n", **words);
		// (*words)++;
		//check_type(**words, ctx);
		return ;
	}
	// printf("+%s+", **words);
	**words =   ft_strtrim(**words);
	printf("\n %s ", **words);

	if (/* *words &&  */ft_strncmp(**words, "location", 8) == 0)
	{
			ctx->parse_obj.loc = read_triple(*words);
			/* (*words)++;
			printf("\t %s ", **words);
			(*words)++;
			printf("\t %s ", **words);
			(*words)++;
			printf("\t %s ", **words); */
			//printf("WE HAVE A LOCATION!_%s_ \n", **words);
	}
	if (/* *words &&  */ft_strncmp(**words, "color", 5) == 0)
	{
//		ctx->parse_obj.loc = read_triple(**words);
			(*words)++;
			printf("\t %s ", **words);
			(*words)++;
			printf("\t %s ", **words);
			(*words)++;
			printf("\t %s \t", **words);
			//printf("WE HAVE A LOCATION!_%s_ \n", **words);
	}
	printf(" \tType id: %d", ctx->parse_obj.type);
	//ft_atoi(*(*words));
	vec_push(obj_vec, &obj);
	//(*words)++;
}

int	load_scene(int fd, t_context *ctx)
{
	char	*line;
	char	**words;
	char	**temp;
	t_vec	obj_vec;

	printf("...\n");
	vec_new(&ctx->scene, BUFF_SIZE * 2, sizeof(t_vec));
	while (get_next_line(fd, &line))
	{
		words = ft_strsplit(line, ' ');
		temp = words;
		if (*temp)
		{
			if (ctx->parse_state == NOTHING && **temp == '{')
			{
				// printf("Hi\n");
				ctx->parse_state = PROCESSING;
				//printf("Checking temp? -%s-%s-", *temp, *(++temp));
				//--temp;
				check_type(temp, ctx);
				
				vec_new(&obj_vec, ft_strlen(line) / 2 + 1, sizeof(t_object));
			}
			else if (**temp == '}')
			{
				// printf("Hello\n");
				ctx->parse_state = NOTHING;
				if (obj_vec.len > 0)
					vec_push(&ctx->scene, &obj_vec);
			}
			else if (ctx->parse_state == PROCESSING)
			{
				// printf("Moi\n");
				process_line(ctx, &words, &obj_vec);
			}
		}
		free_array((void *)&temp);
		ft_strdel(&line);
	}
	return (1);
}
