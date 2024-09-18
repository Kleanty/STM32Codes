#include "adxl345.h"

extern I2C_HandleTypeDef hi2c1;

int ADXL345_ScanDeviceID(I2C_HandleTypeDef *hi2cx) {
    for (uint8_t address = 0; address < 255; ++address) {
        if (HAL_I2C_IsDeviceReady(hi2cx, address << 1, 1, TIMEOUT) == HAL_OK) {
            return address;
        }
    }
    return -1;
}

ADXL345ReadStatus ADXL345_ReadRegisterData(I2C_HandleTypeDef *hi2cx, uint16_t registerAddress, uint16_t sizeofData, uint8_t *dataBuffer) {
    if (HAL_I2C_Mem_Read(hi2cx, ADXL345_DEVICE_ADDRESS << 1, registerAddress, I2C_MEMADD_SIZE_8BIT, dataBuffer, sizeofData, TIMEOUT) == HAL_OK) {
        return READ_SUCCESS;
    } else {
        return READ_FAIL;
    }
}

ADXL345WriteStatus ADXL345_WriteRegisterData(I2C_HandleTypeDef *hi2cx, uint16_t registerAddress, uint16_t value) {
    uint8_t data[2] = {0};
    data[0] = registerAddress;
    data[1] = value;

    if (HAL_I2C_Master_Transmit(hi2cx, ADXL345_DEVICE_ADDRESS << 1, data, sizeof(data), TIMEOUT) == HAL_OK) {
        return Write_SUCCESS;
    }
    return Write_FAIL;
}

ADXL345InitStatus ADXL345_Init(I2C_HandleTypeDef *hi2cx) {
    uint8_t dataBuffer = 0;
    if (ADXL345_ReadRegisterData(hi2cx, DEVID, 1, &dataBuffer) != READ_SUCCESS || dataBuffer != 0xE5) {
        return INIT_FAIL;
    }

    uint8_t tempReg = 0;

    powerControl_Register_t powerControl = {0};
    powerControl.wakeup = WAKEUP_8HZ;
    powerControl.sleep = 0x00;
    powerControl.auto_sleep = 0x00;
    powerControl.measure = 0x01;
    powerControl.reserved = 0x0;
    powerControl.link = 0x00;

    tempReg = *((uint8_t*)&powerControl);
    if (ADXL345_WriteRegisterData(hi2cx, POWER_CTL, tempReg) != Write_SUCCESS) {
        return INIT_FAIL;
    }

    DataFormat_Register_t DataFormat = {0};
    DataFormat.range = RANGE_8G;
    DataFormat.justify = 0x00;
    DataFormat.FULL_RES = 0x00;
    DataFormat.reserved = 0x00;
    DataFormat.INT_INVERT = 0x00;
    DataFormat.SPI = 0x00;
    DataFormat.SELF_TEST = 0x00;

    tempReg = *((uint8_t*)&DataFormat);
    if (ADXL345_WriteRegisterData(hi2cx, DATA_FORMAT, tempReg) != Write_SUCCESS) {
        return INIT_FAIL;
    }

    BWRATERegister_t BWRATEControl = {0};
    BWRATEControl.Range = BANDWIDTH_RATE_800;
    BWRATEControl.LOW_POWER = 0x00;
    BWRATEControl.Reserved = 0x00;

    tempReg = *((uint8_t*)&BWRATEControl);
    if (ADXL345_WriteRegisterData(hi2cx, BW_RATE, tempReg) != Write_SUCCESS) {
        return INIT_FAIL;
    }

    return INIT_SUCCESS;
}

int16_t ADXL345_getAxisValue(I2C_HandleTypeDef *hi2cx, uint8_t axisV) {
    uint8_t data[2] = {0};
    if (ADXL345_ReadRegisterData(hi2cx, axisV, 2, data) != READ_SUCCESS) {
        return 0;
    }
    return (data[0] << 8 | data[1]);
}
