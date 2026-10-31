idf_component_register(SRCS "sd_card_example_main.c"
                       INCLUDE_DIRS "."
                       REQUIRES fatfs sd_card esp_timer driver esp_driver_i2c)