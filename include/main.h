#ifndef MAIN__H
#define MAIN__H

int Mix_OpenAudio(int frequency, Uint16 format, int channels, int chunksize);
int Mix_PlayMusic(Mix_Music *music, int loops);

#endif