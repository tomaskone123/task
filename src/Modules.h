/*
 ******************************************************************************
 *                                                                            *
 *                           esc Aerospace s.r.o.                             *
 *                       https://www.esc-aerospace.com                        *
 *                                                                            *
 *                           ALL RIGHTS RESERVED                              *
 *                                                                            *
 ******************************************************************************
 */

/**
 *  @file Modules.h
 *  @author esc
 *  @brief Definition of enumerate containing names of all modules
 *
 * Copyright 2024 esc Aerospace s.r.o., All rights reserved.
 */

#ifndef __MODULES_H__
#define __MODULES_H__

/* Typedef containing all modules */
typedef enum
{
	E_MODULES_ID_COMM                    = 1U,
	E_MODULES_ID_NVMMEM                  = 2U
} Modules_Id_e;

/* List containing all Event Codes */
typedef enum
{
	EVENT_NVM_ADDRESS_OUT_OF_RANGE,
	EVENT_NVM_NULL_DATA_POINTER,
	EVENT_NVM_ZERO_DATA_SIZE
} EventCode;

/* List containing all Event Severities */
typedef enum {
	EVENT_SEVERITY_NORMAL,
	EVENT_SEVERITY_LOW,
	EVENT_SEVERITY_MEDIUM
} EventSeverity_t;

// struct for the event report variables
typedef struct {
	EventCode eventCode;
	Modules_Id_e moduleId;
	const char *location;
	uint32_t userParam;
	EvenSeverity_t severity;
} EventReport_t;


#endif /* __MODULES_H__ */
