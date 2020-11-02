/*
 * Main
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "driver/gpio.h"
#include <lv_conf.h>
#include "lvgl/lvgl.h"
#include "lv_examples/src/lv_demo_widgets/lv_demo_widgets.h"
#include "esp_freertos_hooks.h"


#include "disp_spi.h"
#include "ili9488.h"

static void IRAM_ATTR lv_tick_task(void);

extern "C" void app_main(void)
{
	lv_init();

	disp_spi_init();
	ili9488_init();

    //todo... move xpt2046 support to the dedicated file...

	//tp_spi_init();
    //xpt2046_init();

    static lv_color_t buf1[DISP_BUF_SIZE];
    static lv_color_t buf2[DISP_BUF_SIZE];

    static lv_disp_buf_t disp_buf;
    lv_disp_buf_init(&disp_buf, buf1, buf2, DISP_BUF_SIZE);

	lv_disp_drv_t disp_drv;
	lv_disp_drv_init(&disp_drv);
	disp_drv.flush_cb = ili9488_flush;
	disp_drv.buffer = &disp_buf;
	lv_disp_drv_register(&disp_drv);

    // Set TOUCH_SUPPORT on drv\component.mk to 1 if
    // your board have touch support
#if ENABLE_TOUCH_INPUT
    lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.read_cb = xpt2046_read;
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    lv_indev_drv_register(&indev_drv);
#endif

	esp_register_freertos_tick_hook(lv_tick_task);

	lv_demo_widgets();

	while(1) {
		vTaskDelay(1);
		lv_task_handler();
	}
}

static void IRAM_ATTR lv_tick_task(void)
{
	lv_tick_inc(portTICK_RATE_MS);
}

/*
 * vim: ts=4 et nowrap autoindent
 */