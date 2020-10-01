#
# Copyright (c) 2018 Nordic Semiconductor
#
# SPDX-License-Identifier: LicenseRef-BSD-5-Clause-Nordic
#

cmake_minimum_required(VERSION 3.13.1)

#include(../../../cmake/boilerplate.cmake)
find_package(Zephyr REQUIRED HINTS C:/Users/Marco/Desktop/NORDICDOC/SDK/zephyr)
project(mqtt-simple3)

# NORDIC SDK APP START
target_sources(app PRIVATE src/main.c)
# NORDIC SDK APP END
