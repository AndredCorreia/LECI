cmake_minimum_required(VERSION 3.22)

# Informa o ESP-IDF onde encontrar os componentes personalizados (dht20, battery, etc.)
set(EXTRA_COMPONENT_DIRS "components")

include($ENV{IDF_PATH}/tools/cmake/project.cmake)

project(EcoNode)