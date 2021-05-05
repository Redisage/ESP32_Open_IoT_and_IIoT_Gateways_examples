/**
 ******************************************************************************
 * @file       my_sntp.h
 * @author     Pawel Wojciechowski / B.P.I. SoftCad
 ******************************************************************************
 * @attention
 * COPYRIGHT 2021 B.P.I. SoftCad. All rights reserved.
 * CONTACT-INFO: info@softcad.com.pl
 ******************************************************************************
 */


void initialize_sntp(void);
void obtain_time(void);
void time_sync_notification_cb(struct timeval *tv);

const char *SNTP_TAG;
