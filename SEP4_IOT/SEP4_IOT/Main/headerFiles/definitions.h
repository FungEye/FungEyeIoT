#pragma once

/**
 * @brief Bit masks for task readiness.
 */
#define BIT_TASK_TEMP_READY (1<<0)    /**< Bit mask indicating readiness of the temperature task. */
#define BIT_TASK_HUM_READY (1<<1)     /**< Bit mask indicating readiness of the humidity task. */
#define BIT_TASK_CO2_READY (1<<2)     /**< Bit mask indicating readiness of the CO2 task. */
#define BIT_TASK_LIGHT_READY (1<<3)   /**< Bit mask indicating readiness of the light task. */

/**
 * @brief Bit masks for task emptiness.
 */
#define BIT_TASK_TEMP_EMPTY (0<<0)    /**< Bit mask indicating the temperature task is empty. */
#define BIT_TASK_HUM_EMPTY (0<<1)     /**< Bit mask indicating the humidity task is empty. */
#define BIT_TASK_CO2_EMPTY (0<<2)     /**< Bit mask indicating the CO2 task is empty. */
#define BIT_TASK_LIGHT_EMPTY (0<<3)   /**< Bit mask indicating the light task is empty. */
