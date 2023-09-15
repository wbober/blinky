#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/led_strip.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(main, LOG_LEVEL_DBG);

#define LED_STRIP_SIZE DT_PROP(DT_NODELABEL(led_strip), chain_length)
const struct device *dev = DEVICE_DT_GET(DT_NODELABEL(led_strip));
struct led_rgb led_rgb[LED_STRIP_SIZE];

int main(void)
{
	int ret;
	int i = 3;

	if (!dev) {
		LOG_ERR("LED strip device not found");
		return 0;
	}

	if (!device_is_ready(dev)) {
		LOG_ERR("LED strip device %s is not ready", dev->name);
		return 0;
	}

	LOG_INF("Found LED strip device %s", dev->name);

	while (1) {
		memset(led_rgb, 0, sizeof(led_rgb));
		led_rgb[3].r = 0xff;
		// led_rgb[3].g = 0xff;
		led_rgb[3].b = 0xff;
		
		ret = led_strip_update_rgb(dev, led_rgb, LED_STRIP_SIZE);	
		if (ret < 0) {
			LOG_ERR("failed to update strip");
		}
		
		k_sleep(K_MSEC(1000));
	}

	return 0;
}
