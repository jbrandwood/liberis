/*
        liberis -- A set of libraries for controlling the NEC PC-FX

Copyright (C) 2011              Alex Marshall "trap15" <trap15@raidenii.net>

# This code is licensed to you under the terms of the MIT license;
# see file LICENSE or http://www.opensource.org/licenses/mit-license.php
*/

/*! \file
 *  \brief Functions to handle V810 specific functionality.
 *
 *  Exposes functions for cache control, IRQ handling, and port usage.
 */

#ifndef _LIBERIS_V810_H_
#define _LIBERIS_V810_H_

#include <eris/types.h>

/* Cache functions */

/*! \brief Enable V810 cache.
 * \sa cache_disable()
 */
void cache_enable(void);
/*! \brief Disable V810 cache.
 * \sa cache_enable()
 */
void cache_disable(void);
/*! \brief Clear select entries in the V810 cache.
 *
 * \param entry The first entry in the cache to clear. (0 ~ 127)
 * \param count The amount of entries to clear from the cache. (1 ~ 128)
 */
void cache_clear(int entry, int count);
/* Must be aligned to 256 byte boundary */
/*! \brief Dump the V810 cache.
 *
 * \param dumpaddr The memory to dump the cache into. Must be 256 byte aligned.
 * \sa cache_restore()
 */
void cache_dump(void* dumpaddr);
/*! \brief Restore the V810 cache.
 *
 * Restores the V810 cache from a dump made with cache_dump().
 * \param restaddr The memory to restore the cache from. Must be 256 byte
 *                 aligned.
 * \sa cache_dump()
 */
void cache_restore(void* restaddr);

/* IRQ functions */

/*! \brief Enable V810 IRQs.
 *
 * \return Returns whether or not IRQs were enabled before. Pass this to
 *         irq_restore() to restore the old IRQ status.
 * \sa irq_disable(), irq_restore()
 */
int irq_enable(void);
/*! \brief Disable V810 IRQs.
 *
 * \return Returns whether or not IRQs were enabled before. Pass this to
 *         irq_restore() to restore the old IRQ status.
 * \sa irq_enable(), irq_restore()
 */
int irq_disable(void);
/*! \brief Restore V810 IRQs.
 *
 * \param on Whether the IRQs should be turned on or off. A return value from
 *           irq_disable() or irq_enable() is also valid.
 * \sa irq_enable(), irq_disable()
 */
void irq_restore(int on);
/*! \brief Set minimum V810 maskable interrupt level.
 *
 * Sets the minimum interrupt level that will be accepted by the interrupt
 * handling in the V810. Any interrupts with a level below this will not be
 * acknowledged.
 * \param lv Minimum V810 maskable interrupt level. (0 ~ 15)
 * \sa irq_get_level()
 */
void irq_set_level(int lv);
/*! \brief Set interrupt masking.
 *
 * Sets the interrupt masking for the interrupt levels 8 ~ 15.
 * \param mask The mask on levels. bit0 is level 15, bit 7 is level 8, etc.
 * \sa irq_get_mask()
 */
void irq_set_mask(int mask);
/*! \brief Set priorities for each interrupt level.
 *
 * Sets interrupt priorities for interrupt levels 8 ~ 15.
 * \param prio The priority for levels. Each level gets 3 bits, with bit0~2
 *             being level 15, and bit29~31 is level 8.
 * \sa irq_get_priority()
 */
void irq_set_priority(u32 prio);
/*! \brief Get minimum/current V810 maskable interrupt level.
 *
 * Gets the current/minimum (they're the same here) maskable interrupt level.
 * \return Current/minimum maskable interrupt level.
 * \sa irq_set_level()
 */
int irq_get_level(void);
/*! \brief Get interrupt masking.
 *
 * Gets the interrupt masking for the interrupt levels 8 ~ 15.
 * \return The mask on levels. bit0 is level 8, bit 7 is level 15, etc.
 * \sa irq_set_mask()
 */
u16 irq_get_mask(void);
/*! \brief Get priorities for each interrupt level.
 *
 * Gets interrupt priorities for interrupt levels 8 ~ 15.
 * \return The priority for levels. Each level gets 3 bits, with bit0~2 being
 *         level 15, and bit29~31 is level 8.
 * \sa irq_set_priority()
 */
u32 irq_get_priority(void);
/*! \brief Set an IRQ handler.
 *
 * Sets a handler for a specific IRQ level.
 * \param level The level that this handler will correspond to.
 * \param fn The handler that will be run when an interrupt with the correct
 *           level is signaled.
 */
void irq_set_handler(int level, void (*fn)(void));
/*! \brief Sets mask to add allowing a single level.
 *
 */
void irq_level_enable(int level);
/*! \brief Sets mask to remove allowing a single level.
 *
 */
void irq_level_disable(int level);
/*! \brief Set an IRQ handler. This one is not wrapped, and as such must be
 * written in assembly.
 *
 * Sets a handler for a specific IRQ level.
 * \param level The level that this handler will correspond to.
 * \param fn The handler that will be run when an interrupt with the correct
 *           level is signaled.
 */
void irq_set_raw_handler(int level, void (*fn)(void));

/* Port functions */

/*! \brief Output 32bit data.
 *
 * \param port Port to output to.
 * \param data Data to be output through the port.
 * \sa out16(), out8()
 */
void out32(u32 port, u32 data);
/*! \brief Output 16bit data.
 *
 * \param port Port to output to.
 * \param data Data to be output through the port.
 * \sa out32(), out8()
 */
void out16(u32 port, u16 data);
/*! \brief Output 8bit data.
 *
 * \param port Port to output to.
 * \param data Data to be output through the port.
 * \sa out32(), out16()
 */
void out8(u32 port, u8 data);
/*! \brief Input 32bit data.
 *
 * \param port Port to input from.
 * \return Data input from the port.
 * \sa in16(), in8()
 */
u32 in32(u32 port);
/*! \brief Input 16bit data.
 *
 * \param port Port to input from.
 * \return Data input from the port.
 * \sa in32(), in8()
 */
u16 in16(u32 port);
/*! \brief Input 8bit data.
 *
 * \param port Port to input from.
 * \return Data input from the port.
 * \sa in32(), in16()
 */
u8 in8(u32 port);

/*! \brief Nullsub conveniently statically located at 0x8004.
 *
 * Not void parameters, so that you can pass in whatever debug info you want.
 */
void dbgbreak();

#endif

