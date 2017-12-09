/* ['Common headers' begin (DON'T REMOVE THIS LINE!)] */
#include "IoT.h"
/* ['Common headers' end (DON'T REMOVE THIS LINE!)] */
#include "prj_cfg.h"
#include "prj_dre.h"
#include "prj_cmd.h"

#ifdef CFG_USE_IOT
/* ['IoTMng' begin (DON'T REMOVE THIS LINE!)] */
void IoTMng(  )
{
    /* set initial state */
    static STATE_T state = ID_IOTMNG_INITIAL;

    switch( state )
    {
        /* State ID: ID_IOTMNG_INITIAL */
        case ID_IOTMNG_INITIAL:
        {
            if( dre.iot_go_online == true )
            {
                /* Transition ID: ID_IOTMNG_TRANSITION_CONNECTION */
                /* Actions: */
                /* ['<global>::iot_connect' begin] */
                dre.iot_disconnect = false;

                dre.iot_connect = true;
                /* ['<global>::iot_connect' end] */
                state = ID_IOTMNG_CONNECTING;
            }
            break;
        }
        /* State ID: ID_IOTMNG_CONNECTING */
        case ID_IOTMNG_CONNECTING:
        {
            if( dre.iot_connected == false )
            {
                /* Transition ID: ID_IOTMNG_TRANSITION_CONNECTION_6 */
                /* Actions: */
                /* ['<global>::iot_connect' begin] */
                dre.iot_disconnect = false;

                dre.iot_connect = true;
                /* ['<global>::iot_connect' end] */
            }
            else if( dre.iot_connected == true )
            {
                /* Transition ID: ID_IOTMNG_TRANSITION_CONNECTION_2 */
                state = ID_IOTMNG_WORKINGONLINE;
            }
            break;
        }
        /* State ID: ID_IOTMNG_WORKINGONLINE */
        case ID_IOTMNG_WORKINGONLINE:
        {
            if( ( dre.iot_go_offline == true ) || ( dre.iot_connected == false ) )
            {
                /* Transition ID: ID_IOTMNG_OPTIMIZED_TRANSITION_1 */
                /* Actions: */
                /* ['<global>::iot_disconnect' begin] */
                dre.iot_connect = false;

                dre.iot_disconnect = true;
                /* ['<global>::iot_disconnect' end] */
                state = ID_IOTMNG_DISCONNECTING;
            }
            break;
        }
        /* State ID: ID_IOTMNG_DISCONNECTING */
        case ID_IOTMNG_DISCONNECTING:
        {
            if( dre.iot_connected == false )
            {
                /* Transition ID: ID_IOTMNG_TRANSITION_CONNECTION_5 */
                state = ID_IOTMNG_WORKINGOFFLINE;
            }
            break;
        }
        /* State ID: ID_IOTMNG_WORKINGOFFLINE */
        case ID_IOTMNG_WORKINGOFFLINE:
        {
            if( dre.iot_go_online == true )
            {
                /* Transition ID: ID_IOTMNG_TRANSITION_CONNECTION_7 */
                /* Actions: */
                /* ['<global>::iot_connect' begin] */
                dre.iot_disconnect = false;

                dre.iot_connect = true;
                /* ['<global>::iot_connect' end] */
                state = ID_IOTMNG_CONNECTING;
            }
            break;
        }
    }
}
/* ['IoTMng' end (DON'T REMOVE THIS LINE!)] */
#endif
#ifdef CFG_USE_IOT
/* ['FuncMngr' begin (DON'T REMOVE THIS LINE!)] */
void FuncMngr(  )
{
    /* set initial state */
    static STATE_T state = ID_FUNCMNGR_INITIAL;

    switch( state )
    {
        /* State ID: ID_FUNCMNGR_INITIAL */
        case ID_FUNCMNGR_INITIAL:
        {
            /* Transition ID: ID_FUNCMNGR_TRANSITION_CONNECTION */
            /* Actions: */
            /* ['<global>::iot_init' begin] */
            dre.iot_go_online = true;

            dre.iot_go_offline = false;

            dre.iot_publish = false;
            /* ['<global>::iot_init' end] */
            state = ID_FUNCMNGR_INIT;
            break;
        }
        /* State ID: ID_FUNCMNGR_INIT */
        case ID_FUNCMNGR_INIT:
        {
            if( dre.iot_connected == true )
            {
                /* Transition ID: ID_FUNCMNGR_TRANSITION_CONNECTION */
                /* Actions: */
                /* ['<global>::iot_cmd_clear' begin] */
                dre.iot_go_online = false;

                dre.iot_go_offline = false;

                dre.iot_publish = false;
                /* ['<global>::iot_cmd_clear' end] */
                /* ['<global>::iot_publish' begin] */
                dre.iot_publish = true;
                /* ['<global>::iot_publish' end] */
                /* ['<global>::iot_pub_timer_rst' begin] */
                dre.iot_publish_timer = 0;
                /* ['<global>::iot_pub_timer_rst' end] */
                state = ID_FUNCMNGR_WORKING;
            }
            else if( dre.iot_connected == false )
            {
                /* Transition ID: ID_FUNCMNGR_TRANSITION_CONNECTION */
                /* Actions: */
                /* ['<global>::iot_dont_publish' begin] */
                dre.iot_publish = false;
                /* ['<global>::iot_dont_publish' end] */
            }
            break;
        }
        /* State ID: ID_FUNCMNGR_WORKING */
        case ID_FUNCMNGR_WORKING:
        {
            if( dre.iot_publish_timer >= CFG_PUBLISH_TIME )
            {
                /* Transition ID: ID_FUNCMNGR_TRANSITION_CONNECTION */
                /* Actions: */
                /* ['<global>::iot_publish' begin] */
                dre.iot_publish = true;
                /* ['<global>::iot_publish' end] */
                /* ['<global>::iot_pub_timer_rst' begin] */
                dre.iot_publish_timer = 0;
                /* ['<global>::iot_pub_timer_rst' end] */
            }
            else if( dre.iot_connected == false )
            {
                /* Transition ID: ID_FUNCMNGR_TRANSITION_CONNECTION */
                /* Actions: */
                /* ['<global>::iot_init' begin] */
                dre.iot_go_online = true;

                dre.iot_go_offline = false;

                dre.iot_publish = false;
                /* ['<global>::iot_init' end] */
                /* ['<global>::iot_dont_publish' begin] */
                dre.iot_publish = false;
                /* ['<global>::iot_dont_publish' end] */
                state = ID_FUNCMNGR_INIT;
            }
            else
            {
                /* Transition ID: ID_FUNCMNGR_TRANSITION_CONNECTION */
                /* Actions: */
                /* ['<global>::iot_pub_tim_incr' begin] */
                dre.iot_publish_timer++;
                /* ['<global>::iot_pub_tim_incr' end] */
                /* ['<global>::iot_dont_publish' begin] */
                dre.iot_publish = false;
                /* ['<global>::iot_dont_publish' end] */
            }
            break;
        }
    }
}
/* ['FuncMngr' end (DON'T REMOVE THIS LINE!)] */
#endif
/* ['Emergency' begin (DON'T REMOVE THIS LINE!)] */
void Emergency(  )
{
    /* set initial state */
    static STATE_T state = ID_EMERGENCY_INITIAL;

    switch( state )
    {
        /* State ID: ID_EMERGENCY_INITIAL */
        case ID_EMERGENCY_INITIAL:
        {
            /* Transition ID: ID_EMERGENCY_TRANSITION_CONNECTION */
            state = ID_EMERGENCY_NORMAL;
            break;
        }
        /* State ID: ID_EMERGENCY_NORMAL */
        case ID_EMERGENCY_NORMAL:
        {
            if( dre.emgcy_button == true )
            {
                /* Transition ID: ID_EMERGENCY_TRANSITION_CONNECTION */
                /* Actions: */
                /* ['<global>::emgcy_tim_rst' begin] */
                dre.emgcy_timer = 0;
                /* ['<global>::emgcy_tim_rst' end] */
                state = ID_EMERGENCY_WARNINGFILTER;
            }
            break;
        }
        /* State ID: ID_EMERGENCY_WARNINGFILTER */
        case ID_EMERGENCY_WARNINGFILTER:
        {
            if( (dre.emgcy_button == true) && (dre.emgcy_timer > CFG_EMGCY_QUALTIME) )
            {
                /* Transition ID: ID_EMERGENCY_TRANSITION_CONNECTION */
                /* Actions: */
                /* ['<global>::emgcy_action' begin] */
                dre.emgcy_action = true;
                /* ['<global>::emgcy_action' end] */
                /* ['<global>::emgcy_tim_rst' begin] */
                dre.emgcy_timer = 0;
                /* ['<global>::emgcy_tim_rst' end] */
                state = ID_EMERGENCY_EMERGENCY;
            }
            else if( dre.emgcy_button == true )
            {
                /* Transition ID: ID_EMERGENCY_TRANSITION_CONNECTION */
                /* Actions: */
                /* ['<global>::emgcy_tim_incr' begin] */
                dre.emgcy_timer++;
                /* ['<global>::emgcy_tim_incr' end] */
            }
            else
            {
                /* Transition ID: ID_EMERGENCY_TRANSITION_CONNECTION */
                state = ID_EMERGENCY_NORMAL;
            }
            break;
        }
        /* State ID: ID_EMERGENCY_EMERGENCY */
        case ID_EMERGENCY_EMERGENCY:
        {
            if( ! ( dre.emgcy_timer >= CFG_EMGCY_ACTTIME ) )
            {
                /* Transition ID: ID_EMERGENCY_TRANSITION_CONNECTION */
                /* Actions: */
                /* ['<global>::emgcy_tim_incr' begin] */
                dre.emgcy_timer++;
                /* ['<global>::emgcy_tim_incr' end] */
            }
            else
            {
                /* Transition ID: ID_EMERGENCY_TRANSITION_CONNECTION */
                state = ID_EMERGENCY_HEALING;
            }
            break;
        }
        /* State ID: ID_EMERGENCY_HEALING */
        case ID_EMERGENCY_HEALING:
        {
            if( ! ( dre.emgcy_button == true ) )
            {
                /* Transition ID: ID_EMERGENCY_TRANSITION_CONNECTION */
                /* Actions: */
                /* ['<global>::emgcy_healed' begin] */
                dre.emgcy_action = false;
                /* ['<global>::emgcy_healed' end] */
                state = ID_EMERGENCY_NORMAL;
            }
            else
            {
                /* Transition ID: ID_EMERGENCY_TRANSITION_CONNECTION */
            }
            break;
        }
    }
}
/* ['Emergency' end (DON'T REMOVE THIS LINE!)] */

/* ['PulsingCmd' begin (DON'T REMOVE THIS LINE!)] */
void PulsingCmd(  )
{
    /* set initial state */
    static STATE_T state = ID_PULSINGCMD_INITIAL;

    switch( state )
    {
        /* State ID: ID_PULSINGCMD_INITIAL */
        case ID_PULSINGCMD_INITIAL:
        {
            /* Transition ID: ID_PULSINGCMD_TRANSITION_CONNECTION */
            state = ID_PULSINGCMD_WAITING;
            break;
        }
        /* State ID: ID_PULSINGCMD_WAITING */
        case ID_PULSINGCMD_WAITING:
        {
            if( dre.pulses_to_send > 0 )
            {
                /* Transition ID: ID_PULSINGCMD_TRANSITION_CONNECTION */
                /* Actions: */
                /* ['<global>::send_pulse' begin] */
                dre.pulse_pin = true;
                dre.pulses_to_send--;
                dre.pulses_timer = 0;
                /* ['<global>::send_pulse' end] */
                state = ID_PULSINGCMD_SENDPULSEUP;
            }
            break;
        }
        /* State ID: ID_PULSINGCMD_SENDPULSEUP */
        case ID_PULSINGCMD_SENDPULSEUP:
        {
            if( dre.pulses_timer >= CFG_PULSE_TIMER_UP )
            {
                /* Transition ID: ID_PULSINGCMD_TRANSITION_CONNECTION */
                /* Actions: */
                /* ['<global>::clear_pulse' begin] */
                dre.pulse_pin = false;
                dre.pulses_timer = 0;
                /* ['<global>::clear_pulse' end] */
                state = ID_PULSINGCMD_SENDPULSEDOWN;
            }
            else
            {
                /* Transition ID: ID_PULSINGCMD_TRANSITION_CONNECTION */
                /* Actions: */
                /* ['<global>::pulse_tim_incr' begin] */
                dre.pulses_timer++;
                /* ['<global>::pulse_tim_incr' end] */
            }
            break;
        }
        /* State ID: ID_PULSINGCMD_SENDPULSEDOWN */
        case ID_PULSINGCMD_SENDPULSEDOWN:
        {
            if( ! ( dre.pulses_timer >= CFG_PULSE_TIMER_DOWN ) )
            {
                /* Transition ID: ID_PULSINGCMD_TRANSITION_CONNECTION */
                /* Actions: */
                /* ['<global>::pulse_tim_incr' begin] */
                dre.pulses_timer++;
                /* ['<global>::pulse_tim_incr' end] */
            }
            else
            {
                /* Transition ID: ID_PULSINGCMD_TRANSITION_CONNECTION */
                state = ID_PULSINGCMD_SENDPULSEEND;
            }
            break;
        }
        /* State ID: ID_PULSINGCMD_SENDPULSEEND */
        case ID_PULSINGCMD_SENDPULSEEND:
        {
            if( dre.pulses_to_send > 0 )
            {
                /* Transition ID: ID_PULSINGCMD_TRANSITION_CONNECTION */
                /* Actions: */
                /* ['<global>::send_pulse' begin] */
                dre.pulse_pin = true;
                dre.pulses_to_send--;
                dre.pulses_timer = 0;
                /* ['<global>::send_pulse' end] */
                state = ID_PULSINGCMD_SENDPULSEUP;
            }
            else
            {
                /* Transition ID: ID_PULSINGCMD_TRANSITION_CONNECTION */
                state = ID_PULSINGCMD_WAITING;
            }
            break;
        }
    }
}
/* ['PulsingCmd' end (DON'T REMOVE THIS LINE!)] */

/* ['ReceiveSysCmd' begin (DON'T REMOVE THIS LINE!)] */
void ReceiveSysCmd(  )
{
    /* set initial state */
    static STATE_T state = ID_RECEIVESYSCMD_INITIAL;

    switch( state )
    {
        /* State ID: ID_RECEIVESYSCMD_INITIAL */
        case ID_RECEIVESYSCMD_INITIAL:
        {
            /* Transition ID: ID_RECEIVESYSCMD_TRANSITION_CONNECTION */
            /* Actions: */
            /* ['<global>::reset_serial_counter' begin] */
            dre.serial_counter = 0;
            /* ['<global>::reset_serial_counter' end] */
            state = ID_RECEIVESYSCMD_WAITING;
            break;
        }
        /* State ID: ID_RECEIVESYSCMD_WAITING */
        case ID_RECEIVESYSCMD_WAITING:
        {
            if( Serial.available() > 0 )
            {
                /* Transition ID: ID_RECEIVESYSCMD_TRANSITION_CONNECTION */
                /* Actions: */
                /* ['<global>::read_serial_byte' begin] */
                dre.incoming_bytes[dre.serial_counter++] = Serial.read();
                /* ['<global>::read_serial_byte' end] */
                state = ID_RECEIVESYSCMD_READCHAR;
            }
            break;
        }
        /* State ID: ID_RECEIVESYSCMD_READCHAR */
        case ID_RECEIVESYSCMD_READCHAR:
        {
            if( dre.incoming_bytes[dre.serial_counter-1] == '\n' )
            {
                /* Transition ID: ID_RECEIVESYSCMD_TRANSITION_CONNECTION */
                /* Actions: */
                /* ['<global>::store_received_command' begin] */
                process_received_command();
                /* ['<global>::store_received_command' end] */
                /* ['<global>::reset_serial_counter' begin] */
                dre.serial_counter = 0;
                /* ['<global>::reset_serial_counter' end] */
                state = ID_RECEIVESYSCMD_WAITING;
            }
            else
            {
                /* Transition ID: ID_RECEIVESYSCMD_TRANSITION_CONNECTION */
                state = ID_RECEIVESYSCMD_WAITING;
            }
            break;
        }
    }
}
/* ['ReceiveSysCmd' end (DON'T REMOVE THIS LINE!)] */

/* ['DispatchSysCmd' begin (DON'T REMOVE THIS LINE!)] */
void DispatchSysCmd(  )
{
    /* set initial state */
    static STATE_T state = ID_DISPATCHSYSCMD_INITIAL;

    switch( state )
    {
        /* State ID: ID_DISPATCHSYSCMD_INITIAL */
        case ID_DISPATCHSYSCMD_INITIAL:
        {
            /* Transition ID: ID_DISPATCHSYSCMD_TRANSITION_CONNECTION */
            /* Actions: */
            /* ['<global>::reset_cmd_storage' begin] */
            dre.cmd_base = 0;
            dre.cmd_counter = 0;
            /* ['<global>::reset_cmd_storage' end] */
            state = ID_DISPATCHSYSCMD_WAITING;
            break;
        }
        /* State ID: ID_DISPATCHSYSCMD_WAITING */
        case ID_DISPATCHSYSCMD_WAITING:
        {
            if( dre.cmd_counter != dre.cmd_base )
            {
                /* Transition ID: ID_DISPATCHSYSCMD_TRANSITION_CONNECTION */
                state = ID_DISPATCHSYSCMD_DECODECMD;
            }
            break;
        }
        /* State ID: ID_DISPATCHSYSCMD_DECODECMD */
        case ID_DISPATCHSYSCMD_DECODECMD:
        {
            if( dre.cmd_storage[dre.cmd_base][0] == 'p' )
            {
                /* Transition ID: ID_DISPATCHSYSCMD_TRANSITION_CONNECTION */
                /* Actions: */
                /* ['<global>::process_pulse_cmd' begin] */
                dre.pulses_to_send += atoi(&(dre.cmd_storage[dre.cmd_base][1]));
                /* ['<global>::process_pulse_cmd' end] */
                state = ID_DISPATCHSYSCMD_PULSECMD;
            }
            else if( (dre.cmd_storage[dre.cmd_base][0] == 'e') )
            {
                /* Transition ID: ID_DISPATCHSYSCMD_TRANSITION_CONNECTION */
                /* Actions: */
                /* ['<global>::process_emgcy_cmd' begin] */
                dre.emgcy_action = (dre.cmd_storage[dre.cmd_base][1] == '1');
                Serial.print("cmd_base: ");Serial.println(dre.cmd_storage[dre.cmd_base][1]);
                /* ['<global>::process_emgcy_cmd' end] */
                state = ID_DISPATCHSYSCMD_EMGCYCMD;
            }
            break;
        }
        /* State ID: ID_DISPATCHSYSCMD_PULSECMD */
        case ID_DISPATCHSYSCMD_PULSECMD:
        {
            if( dre.pulses_to_send == 0 )
            {
                /* Transition ID: ID_DISPATCHSYSCMD_TRANSITION_CONNECTION */
                /* Actions: */
                /* ['<global>::jmp_next_cmd' begin] */
                dre.cmd_base = (dre.cmd_base + 1) % CFG_CMD_STORAGE_SIZE;
                /* ['<global>::jmp_next_cmd' end] */
                state = ID_DISPATCHSYSCMD_WAITING;
            }
            break;
        }
        /* State ID: ID_DISPATCHSYSCMD_EMGCYCMD */
        case ID_DISPATCHSYSCMD_EMGCYCMD:
        {
            if( true /* Instant command */ )
            {
                /* Transition ID: ID_DISPATCHSYSCMD_TRANSITION_CONNECTION */
                /* Actions: */
                /* ['<global>::jmp_next_cmd' begin] */
                dre.cmd_base = (dre.cmd_base + 1) % CFG_CMD_STORAGE_SIZE;
                /* ['<global>::jmp_next_cmd' end] */
                state = ID_DISPATCHSYSCMD_WAITING;
            }
            break;
        }
    }
}
/* ['DispatchSysCmd' end (DON'T REMOVE THIS LINE!)] */
