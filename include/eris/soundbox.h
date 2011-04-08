/*
        liberis -- A set of libraries for controlling the NEC PC-FX

Copyright (C) 2011              Alex Marshall "trap15" <trap15@raidenii.net>

# This code is licensed to you under the terms of the MIT license;
# see file LICENSE or http://www.opensource.org/licenses/mit-license.php
*/

#ifndef _LIBERIS_PSG_H_
#define _LIBERIS_PSG_H_

typedef enum {
	ADPCM_RATE_32000 = 0,
	ADPCM_RATE_16000 = 1,
	ADPCM_RATE_8000 = 2,
	ADPCM_RATE_4000 = 3,
} adpcm_rate;

void eris_psg_set_main_volume(u8 left, u8 right);
void eris_psg_set_freq(u8 chan, u16 freq);
void eris_psg_set_volume(u8 chan, u8 vol, u8 on, u8 dda);
void eris_psg_set_balance(u8 chan, u8 left, u8 right);
void eris_psg_set_channel(u8 chan);
void eris_psg_waveform_data(u8 sample);
void eris_psg_set_noise(u8 chan, u8 freq, u8 enabled);
void eris_psg_set_lfo_freq(u8 freq);
void eris_psg_set_lfo_control(u8 ctl);
void eris_psg_set_adpcm_control(adpcm_rate rate, u8 ch0_liner, u8 ch1_liner, u8 ch0_reset, u8 ch1_reset);
void eris_psg_set_adpcm_volume(u8 chan, u8 left, u8 right);

#endif

