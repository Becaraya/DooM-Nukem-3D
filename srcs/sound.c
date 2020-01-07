/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutricot <hutricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 08:05:41 by hutricot          #+#    #+#             */
/*   Updated: 2020/01/03 14:48:03 by hutricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void son(){
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_AudioSpec want;
	SDL_AudioSpec have;
	SDL_memset (&want, 0, sizeof(want));
	want.freq = 11025;
	want.format = AUDIO_S16;
	want.channels = 1;
	want.samples = 4096;
	int audio = SDL_OpenAudioDevice(NULL, 0, &want, &have, 0);
	SDL_PauseAudioDevice(audio, 0);
	
	Uint8 *buf;
	Uint32 len;

	SDL_Window *w = SDL_CreateWindow("SFX", 64, 126, 480, 480, SDL_WINDOW_SHOWN);
	SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1");
	SDL_Renderer *r = SDL_CreateRenderer(w, -1, 0);

		SDL_LoadWAV("Cartoon-12.wav",&have, &buf, &len);
	int done = 0;
	while (done != 1){
		SDL_Event e;
		while (SDL_PollEvent(&e))
		{
			switch (e.type)
			{
				case SDL_MOUSEBUTTONDOWN:
				{
					SDL_QueueAudio(audio, buf, len);
					while (SDL_GetQueuedAudioSize(audio) > 0)
						SDL_Delay(100);
					break;
				}
				case SDL_QUIT:
					done = 1;
					break;
			}
		}
	}

	
	SDL_CloseAudioDevice(audio);
	SDL_FreeWAV(buf);

	SDL_Quit();
}