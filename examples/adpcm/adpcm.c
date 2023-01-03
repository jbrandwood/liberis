/*
	liberis -- A set of libraries for controlling the NEC PC-FX

Copyright (C) 2011		Alex Marshall "trap15" <trap15@raidenii.net>

# This code is licensed to you under the terms of the MIT license;
# see file LICENSE or http://www.opensource.org/licenses/mit-license.php
*/

#include <eris/types.h>
#include <eris/std.h>
#include <eris/v810.h>
#include <eris/king.h>
#include <eris/tetsu.h>
#include <eris/romfont.h>
#include <eris/pad.h>
#include <eris/low/soundbox.h>
#include "victory.h"

/*
 * Gameblabla :0
 * Credits to OldRover for figuring this out.
 * See also cdda.cue to see how you should lay out your CUE file.
 * Basically, since your game data will be on Track 1, the audio will start from Track 2.
 * 
 * This is actually a C version of the HuC code for controlling CD-DA.
 * For whatever reason, he didn't put the mode in the SCSI command list so i did.
 * Seems to have no adverse affect so far and looping seems to work.
*/

/* Tweak this to allow configuration for 32/16 Khz (right now it's set to 16khz by default) */
void Initialize_ADPCM()
{
	/*
		Bits 0 and 1 set the sample rate.
		- 0 = 32kHz
		- 1 = 16kHz
		- 2 = 8kHz
		- 3 = 4kHz. 
		
		Bits 2 and 3 set linear interpolation for channels 0 and 1, respectively. 
		Bits 4 and 5 reset channels 0 and 1 respectively.
	*/
	eris_low_adpcm_set_control(ADPCM_RATE_16000, 0, 0, 0, 0);
	eris_low_adpcm_set_volume(0, 63, 63);
	eris_low_adpcm_set_volume(1, 63, 63);
}

void Upload_ADPCM_Sample(u16* array, int sizearray)
{
	int i;
	eris_king_set_kram_write(0x2000, 1);
	for(i = 0; i < sizearray-1; i++)
	{
		eris_king_kram_write(array[i]);
	}
}

void Play_ADPCM(int channel)
{
	/*
		0x58 is the ADPCM channel 1 start address.
		This is going to tell KING where to get the ADPCM data from.
		ADPCM data is kept in normal KRAM. Using 0x5C instead of 0x58 does the same for channel 1.
	*/
	if (channel == 1) out16(0x600,0x5C);
	else out16(0x600,0x58);

	/*
		The KRAM address has to be divided by 256. I wrote this out longhand to demonstrate.
	*/
	out16(0x604,(0x2000/256));

	/*
		Now I'm telling KING to set the end address. This is 0x59 for channel 0 and 0x5D for channel 1.
	*/
	if (channel == 1) out16(0x600,0x5D);
	else out16(0x600,0x59);

	/*
		The end address is an absolute address, not a divided one.
		Size should be in unsigned short
		Now that you've told KING the range of the sample, it's time to actually play it.
	*/
	out16(0x604,(0x2000+voxarray_length));


	/*
		0x50 is the register that controls playback for both channels. That also means that you will need to be mindful of samples already playing.
	*/
	out16(0x600,0x50);

	/*
		Finally, play the sample. Bit 0 plays the sample configured for channel 0 and bit 1 plays the sample configured for channel 1.
		Bits 2 and 3 control the sampling rate and use the same scheme as earlier.
		Since I want 16kHz, I set bit 2 on and bit 3 off. So... bit 0 on, bit 1 off, bit 2 on, bit 3 off... value is 5. This plays the ADPCM sample in channel 0 at 16kHz.
		If you need to stop a sample while it's playing, select register 0x50 and send a 0 to the bit of the channel you wish to stop. 
		Writing just 0 to 0x604 will stop both channels.
		You can read 0x604 to see which channels are currently in use, and then just stop either of them if you want to.
		If you set the buffer type to Ring, the sample will playback infinitely until you tell it to stop in this manner... or so the docs state.
		So that pretty much sums up how to use ADPCM on the PC-FX.
	*/
	//out16(0x604,5);
	if (channel == 1) out16(0x604,9);
	else out16(0x604,5);
}

int main(int argc, char *argv[])
{
	u32 paddata, padtype;
	int i;
	u32 str[256];
	u32 pstr[3];
	u32 sstr[3];
	u16 microprog[16];

	eris_king_init();
	eris_tetsu_init();
	
	eris_tetsu_set_priorities(0, 0, 1, 0, 0, 0, 0);
	eris_tetsu_set_7up_palette(0, 0);
	eris_tetsu_set_king_palette(0, 0, 0, 0);
	eris_tetsu_set_rainbow_palette(0);

	eris_king_set_bg_prio(KING_BGPRIO_3, KING_BGPRIO_HIDE, KING_BGPRIO_HIDE, KING_BGPRIO_HIDE, 0);
	eris_king_set_bg_mode(KING_BGMODE_4_PAL, 0, 0, 0);
	/* The last value is the ADPCM KRAM page. I leave it at 0. You can put it at 1, which means you have to set bit 31 when you load a sample into KRAM. */
	eris_king_set_kram_pages(0, 0, 0, 0);

	for(i = 0; i < 16; i++) {
		microprog[i] = KING_CODE_NOP;
	}

	microprog[0] = KING_CODE_BG0_CG_0;
	eris_king_disable_microprogram();
	eris_king_write_microprogram(microprog, 0, 16);
	eris_king_enable_microprogram();

	eris_tetsu_set_palette(0, 0x0088);
	eris_tetsu_set_palette(1, 0xE088);
	eris_tetsu_set_palette(2, 0xE0F0);
	eris_tetsu_set_palette(3, 0x602C);
	eris_tetsu_set_video_mode(TETSU_LINES_262, 0, TETSU_DOTCLOCK_5MHz, TETSU_COLORS_16,
				TETSU_COLORS_16, 0, 0, 1, 0, 0, 0, 0);
	eris_king_set_bat_cg_addr(KING_BG0, 0, 0);
	eris_king_set_bat_cg_addr(KING_BG0SUB, 0, 0);
	eris_king_set_scroll(KING_BG0, 0, 0);
	eris_king_set_bg_size(KING_BG0, KING_BGSIZE_256, KING_BGSIZE_256, KING_BGSIZE_256, KING_BGSIZE_256);
	eris_king_set_kram_read(0, 1);
	eris_king_set_kram_write(0, 1);
	// Clear BG0's RAM
	for(i = 0x0; i < 0x1E00; i++) {
		eris_king_kram_write(0);
	}
	chartou32("ADPCM Example", str);
	printstr(str, 10, 0x8, 1);

	eris_pad_init(0);
	
	/* INITIAL SETUP */
	
	/*
	 * How to convert WAV files to ADPCM for PC-FX :
	 * wav2vox -fhuc6230 victory.wav
	 * 
	 * wav2vox can be lifted from Elmer's github fork of Huc :
	 * https://github.com/jbrandwood/huc/tree/master/src/tools/wav2vox
	 * 
	*/

	/* This part plays an ADPCM Sample */
	Initialize_ADPCM();
	Upload_ADPCM_Sample(voxarray, voxarray_length);
	Play_ADPCM(0);
	
	for(;;)
	{

	}

	return 0;
}

void chartou32(char* str, u32* o)
{
	int i;
	int len = strlen8(str);
	for(i = 0; i < len; i++)
		o[i] = str[i];
	o[i] = 0;
}

void printstr(u32* str, int x, int y, int tall)
{
	int i;
	u32 kram = x + (y << 5);
	int len = strlen32(str);
	for(i = 0; i < len; i++) {
		printch(str[i], kram + i, tall);
	}
}

void printch(u32 sjis, u32 kram, int tall)
{
	u16 px;
	int x, y;
	u8* glyph = eris_romfont_get(sjis, tall ? ROMFONT_ANK_8x16 : ROMFONT_ANK_8x8);
	for(y = 0; y < (tall ? 16 : 8); y++) {
		eris_king_set_kram_write(kram + (y << 5), 1);
		px = 0;
		for(x = 0; x < 8; x++) {
			if((glyph[y] >> x) & 1) {
				px |= 1 << (x << 1);
			}
		}
		eris_king_kram_write(px);
	}
}

