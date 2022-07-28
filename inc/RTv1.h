/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RTv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 16:16:55 by jsaarine          #+#    #+#             */
/*   Updated: 2022/07/28 18:43:47 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../libsdl2/include/SDL.h"
# include "SDL.h"


typedef struct s_context
{
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	SDL_Surface 	*screen_surface;
} t_context;

void	tests();
int		init(t_context *ctx);
void	close(t_context *ctx);

