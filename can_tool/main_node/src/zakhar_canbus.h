// *************************************************************************
//
// Copyright (c) 2021 Andrei Gramakov. All rights reserved.
//
// This file is licensed under the terms of the MIT license.
// For a copy, see: https://opensource.org/licenses/MIT
//
// site:    https://agramakov.me
// e-mail:  mail@agramakov.me
//
// *************************************************************************

#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

    typedef enum
    {
        ZCANID_MOTORS_STATUS = 0x2AF,
        ZCANID_MOTORS_CMD = 0x2A0,
        ZCANID_MOTORS_ANGLES = 0x2A1,

        ZCANID_SENSORS_STATUS = 0x2BF,
        ZCANID_SENSORS_CMD = 0x2BE,
        ZCANID_SENSORS_DISTANCE = 0x2B0,
        ZCANID_SENSORS_LIGHT = 0x2B1,

        ZCANID_FACE_STATUS = 0x2CF,
        ZCANID_FACE_CMD = 0x2C0,
    } ZCANID_t;

    typedef enum
    {
        ZCANDATA_CMD_COMMAND = 0x00,
        ZCANDATA_CMD_ARG0,
        ZCANDATA_CMD_ARG1,
        ZCANDATA_CMD_ARG2,
        ZCANDATA_CMD_ARG3,
        ZCANDATA_CMD_ARG4,
        ZCANDATA_CMD_ARG5,
        ZCANDATA_CMD_ARG6,
        ZCANDATA_CMD_ARG7,
    } ZCANDATA_CMD_t;

    typedef enum
    {
        ZCANDATA_MOTORS_STATUS_MODE = 0x00,
        ZCANDATA_MOTORS_STATUS_SPEED,
    } ZCANDATA_MOTORS_STATUS_t;

    typedef enum
    {
        ZCANDATA_MOTORS_ANGLES_X_SIGN = 0x00,
        ZCANDATA_MOTORS_ANGLES_X,
        ZCANDATA_MOTORS_ANGLES_Y_SIGN,
        ZCANDATA_MOTORS_ANGLES_Y,
        ZCANDATA_MOTORS_ANGLES_Z_SIGN,
        ZCANDATA_MOTORS_ANGLES_Z,
    } ZCANDATA_MOTORS_ANGLES_t;

    typedef enum
    {
        ZCANDATA_SENSORS_STATUS_AMMOUNT = 0x00
    } ZCANDATA_SENSORS_STATUS_t;

    typedef enum
    {
        ZCANDATA_SENSORS_DISTANCE_LEFT = 0x00,
        ZCANDATA_SENSORS_DISTANCE_CENTER,
        ZCANDATA_SENSORS_DISTANCE_RIGHT,
    } ZCANDATA_SENSORS_DISTANCE_t;

    typedef enum
    {
        ZCANDATA_SENSORS_LIGHT_LO = 0x00,
        ZCANDATA_SENSORS_LIGHT_HI,
    } ZCANDATA_SENSORS_LIGHT_t;

    typedef enum
    {
        ZCANDATA_FACE_STATUS_EMOTION = 0x00
    }ZCANDATA_FACE_STATUS_t;

#ifdef __cplusplus
}
#endif
