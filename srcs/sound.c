/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutricot <hutricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 08:05:41 by hutricot          #+#    #+#             */
/*   Updated: 2019/12/30 08:20:20 by hutricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void son()
{
/* On déclare la variable qui représentera notre musique une fois chargée */
    Mix_Music* myMus;

    /* On initialise le son */
    SDL_Init(SDL_INIT_AUDIO);

    /* On ouvre un device audio */
    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024);
    printf("tout vas bien \n");
    /* On charge un fichier musical */
    myMus = Mix_LoadMUS("b.ogg");
    if(myMus)
        printf("finalement non \n");
    /* On lance la musique */
    Mix_PlayMusic(myMus, 1);

    while (Mix_PlayingMusic() == 1)
    {
        /* Tant que la musique n'est pas terminée, on fait quelque chose
           car sinon le programme s'éteint et le son aussi */
        SDL_Delay(10);
    }

    /* La musique est terminée, on la libère */
    Mix_FreeMusic(myMus);

    /* On libère le matériel */
    Mix_CloseAudio();
}