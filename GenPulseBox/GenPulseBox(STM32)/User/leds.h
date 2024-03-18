#ifndef  __LEDS_H
#define __LEDS_H

#include "stm32f4xx.h"
#include "main.h"
// PI8 - Debug R, PH2 - Debug B, PH3 - Debug G
// PI0 - PWR R, PI1 - PWR B, PI2 - PWR G,
// PH4 - CH1(1) R, PH6 - CH1(1) B, PH5 - CH1(1) G,
// PH10 - CH1(2) R, PH11 - CH1(2) B, PH12 - CH1(2) G,
// PH7 - CH2(1) R, PH8 - CH2(1) B, PH9 - CH2(1) G,
// PH13 - CH2(2) R, PH15 - CH2(2) B, PH14 - CH2(2) G,
///////////////////////// Led Debug
#define led_debug_r_on 	GPIO_ResetBits(GPIOI, GPIO_Pin_8);
#define led_debug_r_off	GPIO_SetBits(GPIOI, GPIO_Pin_8);
#define led_debug_r_change	if (GPIOI->ODR & GPIO_ODR_ODR_8) {led_debug_r_on} else {led_debug_r_off}

#define led_debug_b_on 	GPIO_ResetBits(GPIOH, GPIO_Pin_2);
#define led_debug_b_off	GPIO_SetBits(GPIOH, GPIO_Pin_2);
#define led_debug_b_change	if (GPIOH->ODR & GPIO_ODR_ODR_2) {led_debug_b_on} else {led_debug_b_off}

#define led_debug_g_on 	GPIO_ResetBits(GPIOH, GPIO_Pin_3);
#define led_debug_g_off	GPIO_SetBits(GPIOH, GPIO_Pin_3);
#define led_debug_g_change	if (GPIOH->ODR & GPIO_ODR_ODR_3) {led_debug_g_on} else {led_debug_g_off}

///////////////////////// Led PWR
#define led_pwr_r_on 	GPIO_ResetBits(GPIOI, GPIO_Pin_0);
#define led_pwr_r_off	GPIO_SetBits(GPIOI, GPIO_Pin_0);
#define led_pwr_r_change	if (GPIOI->ODR & GPIO_ODR_ODR_0) {led_pwr_r_on} else {led_pwr_r_off}

#define led_pwr_b_on 	GPIO_ResetBits(GPIOI, GPIO_Pin_1);
#define led_pwr_b_off	GPIO_SetBits(GPIOI, GPIO_Pin_1);
#define led_pwr_b_change	if (GPIOI->ODR & GPIO_ODR_ODR_1) {led_pwr_b_on} else {led_pwr_b_off}

#define led_pwr_g_on 	GPIO_ResetBits(GPIOI, GPIO_Pin_2);
#define led_pwr_g_off	GPIO_SetBits(GPIOI, GPIO_Pin_2);
#define led_pwr_g_change	if (GPIOI->ODR & GPIO_ODR_ODR_2) {led_pwr_g_on} else {led_pwr_g_off}

///////////////////////// Led CH1(1)
#define led_ch11_r_on 	GPIO_ResetBits(GPIOH, GPIO_Pin_4);
#define led_ch11_r_off	GPIO_SetBits(GPIOH, GPIO_Pin_4);
#define led_ch11_r_change	if (GPIOH->ODR & GPIO_ODR_ODR_4) {led_ch11_r_on} else {led_ch11_r_off}

#define led_ch11_b_on 	GPIO_ResetBits(GPIOH, GPIO_Pin_5);
#define led_ch11_b_off	GPIO_SetBits(GPIOH, GPIO_Pin_5);
#define led_ch11_b_change	if (GPIOH->ODR & GPIO_ODR_ODR_5) {led_ch11_b_on} else {led_ch11_b_off}

#define led_ch11_g_on 	GPIO_ResetBits(GPIOH, GPIO_Pin_6);
#define led_ch11_g_off	GPIO_SetBits(GPIOH, GPIO_Pin_6);
#define led_ch11_g_change	if (GPIOH->ODR & GPIO_ODR_ODR_6) {led_ch11_g_on} else {led_ch11_g_off}

///////////////////////// Led CH1(2)
#define led_ch12_r_on 	GPIO_ResetBits(GPIOH, GPIO_Pin_10);
#define led_ch12_r_off	GPIO_SetBits(GPIOH, GPIO_Pin_10);
#define led_ch12_r_change	if (GPIOH->ODR & GPIO_ODR_ODR_10) {led_ch12_r_on} else {led_ch12_r_off}

#define led_ch12_b_on 	GPIO_ResetBits(GPIOH, GPIO_Pin_11);
#define led_ch12_b_off	GPIO_SetBits(GPIOH, GPIO_Pin_11);
#define led_ch12_b_change	if (GPIOH->ODR & GPIO_ODR_ODR_11) {led_ch12_b_on} else {led_ch12_b_off}

#define led_ch12_g_on 	GPIO_ResetBits(GPIOH, GPIO_Pin_12);
#define led_ch12_g_off	GPIO_SetBits(GPIOH, GPIO_Pin_12);
#define led_ch12_g_change	if (GPIOH->ODR & GPIO_ODR_ODR_12) {led_ch12_g_on} else {led_ch12_g_off}

///////////////////////// Led CH2(1)
#define led_ch21_r_on 	GPIO_ResetBits(GPIOH, GPIO_Pin_7);
#define led_ch21_r_off	GPIO_SetBits(GPIOH, GPIO_Pin_7);
#define led_ch21_r_change	if (GPIOH->ODR & GPIO_ODR_ODR_7) {led_ch21_r_on} else {led_ch21_r_off}

#define led_ch21_b_on 	GPIO_ResetBits(GPIOH, GPIO_Pin_8);
#define led_ch21_b_off	GPIO_SetBits(GPIOH, GPIO_Pin_8);
#define led_ch21_b_change	if (GPIOH->ODR & GPIO_ODR_ODR_8) {led_ch21_b_on} else {led_ch21_b_off}

#define led_ch21_g_on 	GPIO_ResetBits(GPIOH, GPIO_Pin_9);
#define led_ch21_g_off	GPIO_SetBits(GPIOH, GPIO_Pin_9);
#define led_ch21_g_change	if (GPIOH->ODR & GPIO_ODR_ODR_9) {led_ch21_g_on} else {led_ch21_g_off}

///////////////////////// Led CH2(2)
#define led_ch22_r_on 	GPIO_ResetBits(GPIOH, GPIO_Pin_13);
#define led_ch22_r_off	GPIO_SetBits(GPIOH, GPIO_Pin_13);
#define led_ch22_r_change	if (GPIOH->ODR & GPIO_ODR_ODR_13) {led_ch22_r_on} else {led_ch22_r_off}

#define led_ch22_b_on 	GPIO_ResetBits(GPIOH, GPIO_Pin_14);
#define led_ch22_b_off	GPIO_SetBits(GPIOH, GPIO_Pin_14);
#define led_ch22_b_change	if (GPIOH->ODR & GPIO_ODR_ODR_14) {led_ch22_b_on} else {led_ch22_b_off}

#define led_ch22_g_on 	GPIO_ResetBits(GPIOH, GPIO_Pin_15);
#define led_ch22_g_off	GPIO_SetBits(GPIOH, GPIO_Pin_15);
#define led_ch22_g_change	if (GPIOH->ODR & GPIO_ODR_ODR_15) {led_ch22_g_on} else {led_ch22_g_off}

void leds_init(void); // Инициализация светодиодов
void led_off(void);		// Отключение всех светодиодов
void led_control(void);
void led_blink_on_device(void);

#endif
