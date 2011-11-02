/*
        liberis -- A set of libraries for controlling the NEC PC-FX

Copyright (C) 2011              Alex Marshall "trap15" <trap15@raidenii.net>

# This code is licensed to you under the terms of the MIT license;
# see file LICENSE or http://www.opensource.org/licenses/mit-license.php
*/

/*! \file
 * \brief Utilize the built-in timer.
 */

#ifndef _LIBERIS_TIMER_H_
#define _LIBERIS_TIMER_H_

#include <eris/types.h>

/*! \brief Initialize the timer.
 */
void eris_timer_init(void);
/*! \brief Set the period of the timer.
 *
 * Period is in ticks of CPUclk/15. New period will not load until either the
 * timer is restarted, or expires.
 * \brief period The period of the timer. (1 ~ 65535)
 */
void eris_timer_set_period(int period);
/*! \brief Read the current value of the timer.
 *
 * \return The current value of the timer.
 */
int eris_timer_read_counter(void);
/*! \brief Acknowledge a timer IRQ.
 */
void eris_timer_ack_irq(void);
/*! \brief Read the timer's control register.
 *
 * \return The control register.
 */
u16 eris_timer_read_control(void);
/*! \brief Write the timer's control register.
 *
 * \param cr The new control register.
 */
void eris_timer_write_control(int cr);
/*! \brief Start the timer.
 *
 * \param irq If 1, fire an IRQ at timer expiration.
 */
void eris_timer_start(int irq);
/*! \brief Stop the timer.
 */
void eris_timer_stop(void);

#endif

