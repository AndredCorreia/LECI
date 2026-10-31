idf_build_get_property(idf_target IDF_TARGET)

set(component_requires esp_https_server nvs_flash esp_driver_i2c)

if("${idf_target}" STREQUAL "linux")
    list(APPEND component_requires esp_stubs protocol_examples_common)
else()
    list(APPEND component_requires esp_wifi esp_eth)
endif()

idf_component_register(SRCS "main.c"
                    INCLUDE_DIRS "."
                    PRIV_REQUIRES ${component_requires}
                    EMBED_TXTFILES "certs/servercert.pem"
                                   "certs/prvtkey.pem"
                                   "certs/cacert.pem"
                                   "certs/cakey.pem")