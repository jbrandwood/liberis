/*
        liberis -- A set of libraries for controlling the NEC PC-FX

Copyright (C) 2011              Alex Marshall "trap15" <trap15@raidenii.net>

# This code is licensed to you under the terms of the MIT license;
# see file LICENSE or http://www.opensource.org/licenses/mit-license.php
*/

/*! \file
 * \brief Low-level access to the SoundBox.
 */

#ifndef _LIBERIS_LOW_SOUNDBOX_H_
#define _LIBERIS_LOW_SOUNDBOX_H_

/*! \brief ADPCM sample rate.
 */
typedef enum {
	ADPCM_RATE_32000 = 0, /*!< 32kHz sample rate */
	ADPCM_RATE_16000 = 1, /*!< 16kHz sample rate */
	ADPCM_RATE_8000  = 2, /*!< 8kHz sample rate */
	ADPCM_RATE_4000  = 3, /*!< 4kHz sample rate */
} adpcm_rate;

/*! \brief Set main volume.
 *
 * \param left Left speaker output volume. (0 ~ 15)
 * \param right Right speaker output volume. (0 ~ 15)
 */
void eris_low_psg_set_main_volume(u8 left, u8 right);
/*! \brief Set the active channel to operate on.
 *
 * This affects which channel is changed for the functions
 * eris_low_psg_set_freq(), eris_low_psg_set_volume(),
 * eris_low_psg_set_balance(), eris_low_psg_waveform_data(),
 * and eris_low_psg_set_noise().
 * \param chan The channel to become active. (0 ~ 5)
 */
void eris_low_psg_set_channel(u8 chan);
/*! \brief Set the frequency of the active channel.
 *
 * \param freq The frequency of the channel. 12bit. Calculated as 
 *             n = (3580000 / 32) / freq
 */
void eris_low_psg_set_freq(u16 freq);
/*! \brief Set the volume (and some controls) of the active channel.
 *
 * \param vol Volume of the channel. (0 ~ 31)
 * \param on Controls whether the channel is on or off.
 * \param dda Direct DAC access control. When enabled, waveform data is
 *            streamed through eris_low_psg_waveform_data().
 */
void eris_low_psg_set_volume(u8 vol, u8 on, u8 dda);
/*! \brief Set the balance on the active channel.
 * 
 * \param left Left speaker output volume. (0 ~ 15)
 * \param right Right speaker output volume. (0 ~ 15)
 */
void eris_low_psg_set_balance(u8 left, u8 right);
/*! \brief Write waveform data for the active channel.
 *
 * If DDA is off, writes to the waveform buffer and increases the index.
 * If it's on, it changes the current sample being played.
 * \param sample A 5bit unsigned sample. (0 ~ 31)
 */
void eris_low_psg_waveform_data(u8 sample);
/*! \brief Set noise control data for the active channel.
 *
 * Only works on the last 2 channels (4 and 5).
 * \param freq Frequency of the noise. 5bit. Calculated as 
 *             n = (3580000 / 32) / freq
 * \param enabled Whether the channel should or should not output noise.
 */
void eris_low_psg_set_noise(u8 freq, u8 enabled);
/*! \brief Set LFO frequency.
 *
 * \param freq The LFO's new frequency value. Influence is not simple; see
 *             hardware documentation.
 */
void eris_low_psg_set_lfo_freq(u8 freq);
/*! \brief Set LFO controls.
 *
 * \param on Whether the LFO is enabled or not.
 * \param ctrl LFO control. Influence is not simple; see hardware
 *             documentation.
 */
void eris_low_psg_set_lfo_control(int on, int ctrl);
/*! \brief Set ADPCM controls.
 *
 * \param rate Sample rate for the ADPCM.
 * \param ch0_interp Whether Channel 0 has linear interpolation enabled.
 * \param ch1_interp Whether Channel 1 has linear interpolation enabled.
 * \param ch0_reset If set, reset Channel 0.
 * \param ch1_reset If set, reset Channel 1.
 */
void eris_low_adpcm_set_control(adpcm_rate rate, u8 ch0_interp, u8 ch1_interp,
			u8 ch0_reset, u8 ch1_reset);
/*! \brief Set ADPCM channel volume.
 *
 * \param chan Which channel to set the volume of.
 * \param left Left speaker volume. (0 ~ 63)
 * \param right Right speaker volume. (0 ~ 63)
 */
void eris_low_adpcm_set_volume(u8 chan, u8 left, u8 right);
/*! \brief Set CDDA volume.
 *
 * \param left Left speaker volume. (0 ~ 63)
 * \param right Right speaker volume. (0 ~ 63)
 */
void eris_low_cdda_set_volume(u8 left, u8 right);

#endif

