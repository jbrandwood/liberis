#include <eris/types.h>
#include <eris/v810.h>
#include <eris/king.h>
#include <eris/7up.h>
#include <eris/tetsu.h>

int main(int argc, char *argv[])
{
	int i;
	u16 microprog[8];

	eris_7up_init(0);
	eris_7up_init(1);
	eris_king_init();
	eris_tetsu_init();
//	irq_enable();
	
	eris_tetsu_set_priorities(0, 0, 0, 1, 0, 0, 0);
	eris_tetsu_set_7up_palette(0, 0);
	eris_tetsu_set_king_palette(0, 0, 0, 0);
	eris_tetsu_set_rainbow_palette(0);

	eris_king_set_bg_prio(KING_BGPRIO_3, KING_BGPRIO_HIDE, KING_BGPRIO_HIDE, KING_BGPRIO_HIDE, KING_BGPRIO_HIDE);
	eris_king_set_bg_mode(KING_BGMODE_4_PAL, KING_BGMODE_4_PAL, KING_BGMODE_4_PAL, KING_BGMODE_4_PAL);
	eris_king_set_bg_size(KING_BG0, KING_BGSIZE_256, KING_BGSIZE_256, KING_BGSIZE_256, KING_BGSIZE_256);

	for(i = 0; i < 8; i++) {
		microprog[i] = 0x100; /* NOP */
	}

	microprog[0] = 0x0; /* CG0 */
	eris_king_disable_microprogram();
	eris_king_write_microprogram(microprog, 0, 8);
	eris_king_enable_microprogram();

	eris_tetsu_set_palette(0, 0xE0FF);
	eris_tetsu_set_video_mode(TETSU_LINES_262, 0, TETSU_DOTCLOCK_5MHz, TETSU_COLORS_16,
				TETSU_COLORS_16, 0, 0, 1, 0, 0, 0, 0);

	return 0;
}

