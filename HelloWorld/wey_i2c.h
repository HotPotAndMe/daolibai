/*
 * wind_i2c.h
 *
 *  Created on: 2016Äê12ÔÂ7ÈÕ
 *      Author: weycen
 */

#ifndef WEY_I2C_H_
#define WEY_I2C_H_


extern uint32_t I2CWriteRegOneByte(uint32_t ui32I2CBase,uint8_t ui8SlaAddr,
        uint8_t ui8RegAddr, uint8_t ui8RegData);

extern uint32_t I2CWriteRegTwoByte(uint32_t ui32I2CBase,uint8_t ui8SlaAddr,
        uint8_t ui8RegAddr, uint16_t ui16RegData);

extern uint32_t I2CWriteRegMultiByte(uint32_t ui32I2CBase,uint8_t ui8SlaAddr,
        uint8_t ui8RegAddr, uint8_t *pui8RegData, uint32_t ui32WriteCount);

extern uint32_t I2CReadRegOneByte(uint32_t ui32I2CBase, uint8_t ui8SlaAddr,
        uint8_t ui8RegAddr, uint8_t *pui8RegData);

extern uint32_t I2CReadRegTwoByte(uint32_t ui32I2CBase, uint8_t ui8SlaAddr,
        uint8_t ui8RegAddr, uint16_t *pui16RegData);

extern uint32_t I2CReadRegMultiByte(uint32_t ui32I2CBase, uint8_t ui8SlaAddr,
        uint8_t ui8RegAddr,uint8_t *pui8RegData, uint32_t ui32ReadCount);


#endif /* WEY_I2C_H_ */
