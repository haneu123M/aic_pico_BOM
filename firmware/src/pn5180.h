/*
 * PN5180 NFC Reader
 * WHowe <github.com/whowechina>
 * 
 */

#ifndef PN5180_H
#define PN5180_H

#include "hardware/spi.h"

#define PN5180_REG_SYSTEM_CONFIG 0x00
#define PN5180_REG_IRQ_ENABLE 0x01
#define PN5180_REG_IRQ_STATUS 0x02
#define PN5180_REG_IRQ_CLEAR 0x03
#define PN5180_REG_RX_STATUS 0x13
#define PN5180_REG_RF_STATUS 0x1d
#define PN5180_REG_CRC_RX_CONFIG 0x12
#define PN5180_REG_CRC_TX_CONFIG 0x19

typedef void (*pn5180_wait_loop_t)();

void pn5180_set_wait_loop(pn5180_wait_loop_t loop);

void pn5180_init(spi_inst_t *port, uint8_t rx, uint8_t sck, uint8_t tx,
                 uint8_t rst, uint8_t nss, uint8_t busy);

void pn5180_write_reg(uint8_t reg, uint32_t v32);
void pn5180_or_reg(uint8_t reg, uint32_t mask);
void pn5180_and_reg(uint8_t reg, uint32_t mask);
uint32_t pn5180_read_reg(uint8_t reg);
void pn5180_send_data(const uint8_t *data, uint8_t len, uint8_t last_bits);
void pn5180_read_data(uint8_t *data, uint8_t len);
void pn5180_read_eeprom(uint8_t addr, uint8_t *buf, uint8_t len);

void pn5180_load_rf_config(uint8_t tx_cfg, uint8_t rx_cfg);
void pn5180_rf_on();
void pn5180_rf_off();

uint32_t pn5180_get_irq();
void pn5180_clear_irq(uint32_t mask);
uint32_t pn5180_get_rx();

void pn5180_reset();

bool pn5180_poll_mifare(uint8_t *uid, int *len);
bool pn5180_poll_felica(uint8_t uid[8], uint8_t pmm[8], uint8_t syscode[2], bool from_cache);
bool pn5180_poll_vicinity(uint8_t *uid, int *len);

void pn5180_print_rf_cfg();

#endif
