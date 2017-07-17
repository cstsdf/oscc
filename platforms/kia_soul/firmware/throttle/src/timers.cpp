/**
 * @file timers.cpp
 *
 */


#include "throttle_can_protocol.h"
#include "oscc_timer.h"

#include "timers.h"
#include "globals.h"
#include "communications.h"
#include "throttle_control.h"


/*
 * @brief Fault checking frequency. [Hz]
 *
 */
#define FAULT_CHECK_FREQUENCY_IN_HZ ( 10 )


static void check_for_faults( void );


void start_timers( void )
{
    timer1_init( FAULT_CHECK_FREQUENCY_IN_HZ, check_for_faults );
    timer2_init( OSCC_REPORT_THROTTLE_PUBLISH_FREQ_IN_HZ, publish_throttle_report );
}


static void check_for_faults( void )
{
    check_for_controller_command_timeout( );

    check_for_sensor_faults( );

    g_throttle_command_timeout = true;
}