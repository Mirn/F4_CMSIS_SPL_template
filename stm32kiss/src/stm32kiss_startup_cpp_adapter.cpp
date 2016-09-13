/* stm32kiss_startup_cpp_adapter.cpp
 *
 *  Created on: 05 θώνÿ 2014 γ.
 *      Author: Easy
 */

#include <stdint.h>

extern "C" {
uint32_t kiss_startup_init();
}

volatile uint8_t kiss_startup_adapter = kiss_startup_init();
