/*
 * notePlay.h
 *
 *  Created on: May 14, 2020
 *      Author: sergio_mndz
 */

#ifndef MENDEZ_EX2_NOTEPLAY_H_
#define MENDEZ_EX2_NOTEPLAY_H_

void initPlayer();

void play_Signal();

void play_Manual(uint8_t note);

void play_Sequence(uint8_t* array, uint8_t len);

#endif /* MENDEZ_EX2_NOTEPLAY_H_ */
