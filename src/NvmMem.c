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
 *  @file NvmMem.c
 *  @author esc
 *  @brief  This module is used to write data into the non-volatile memory.
 *
 * Copyright 2024 esc Aerospace s.r.o., All rights reserved.
 */

#include "NvmMem.h"
#include "Modules.h"
#include "Comm.h"

#define NVM_ADDRESS_LOW_LIM     (0x00001000)
#define NVM_ADDRESS_HIGH_LIM    (0x00200000)

/* Module ID assignment */
static const Modules_Id_e m_eModuleId = E_MODULES_ID_NVMMEM;


/**
 * @brief Writes data to the non-volatile memory at the specific address
 *
 * @param in_u32Address     Target memory address
 * @param in_pu8Data        Data to be written
 * @param in_u32DataSize    Size of the data in bytes
 */

/* Function to write data byte to a address */
static void	Nvm_WritByte(uint32_t address, uint8_t data)
{
	*((volatile uint*_t*)address) = data;
}

void NvmMem_Write(uint32_t in_u32Address, const uint8_t *in_pu8Data, uint32_t in_u32DataSize)
{
    /* Address range check */
    if ((NVM_ADDRESS_LOW_LIM > in_u32Address) || (NVM_ADDRESS_HIGH_LIM < in_u32Address))
    {
        EventReport_t event = {
			EVENT_NVM_ADDRESS_OUT_OF_RANGE,	/* event code */
			m_eModuleId,					/* module Id */
			"NvmMem_Write",					/* location of function where the event was generated */
			in_u32Address,					/* user parameter */
			EVENT_SEVERITY_LOW				/* Severity of the event */
		};
		Comm_SendEventReport((const uint8_t*)&event, sizeof(event));
        return;
    }

    /* Data validity check */
    if (NULL == in_pu8Data)
    {
        EventReport_t event = {
			EVENT_NVM_NULL_DATA_POINTER,	/* event code */
			m_eModuleId,					/* module Id */
			"NvmMem_Write",					/* location of function where the event was generated */
			0,								/* user parameter */
			EVENT_SEVERITY_MEDIUM			/* Severity of the event */
		};
		Comm_SendEventReport((const uint8_t*)&event, sizeof(event));
        return;
    }

    /* Minimum data length check */
    if (0U == in_u32DataSize)
    {
        EventReport_t event = {
			EVENT_NVM_ZERO_DATA_SIZE,
			m_eModuleId,
			"NvmMem_Write",
			0,
			EVENT_SEVERITY_NORMAL
		};
		Comm_SendEventReport((const char*)&event, sizeof(event));
        return;
    }
    /* ... MEMORY WRITING IMPLEMENTATION ... */
	uint32_t	i = 0;
	while (i < in_u32DataSize)
	{
		Nvm_WriteByte(in_u32Address + i, in_pu8Data[i]);
		i++;
	}
    return;
}
