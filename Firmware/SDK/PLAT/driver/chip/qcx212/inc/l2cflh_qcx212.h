#ifndef __L2C_FLH_AES_H__
#define __L2C_FLH_AES_H__
enum {
    AES_ENCRYPT  = 0,
    AES_DECRYPT,
    AES_TYPE_MAX,
};

enum {
    AES_CHAIN_ECB =  0,
    AES_CHAIN_CBC,
    AES_CHAIN_MAX
};

enum {
    AES_KEY_SIZE_128  = 0,
    AES_KEY_SIZE_192,
    AES_KEY_SIZE_256,
    AES_KEY_SIZE_MAX,
};

enum {
    AES_KEY_TYPE_RNG = 0,
    AES_KEY_TYPE_SOFTWARE,
    AES_KEY_TYPE_MAX,
};

enum {
    AES_PADDING_NONE = 0,
    AES_PADDING_PKCS7,
    AES_PADDING_ONEZEROS,
    AES_PADDING_ZEROSLEN,
    AES_PADDING_ZEROS,
    AES_PADDING_MAX,
};

typedef struct 
{
    uint32_t Encrypt : 1;  //0: Encrypt, 1:Decrypt
    uint32_t ChainMode : 2; //0:ECB, 1: CBC, 2/3:Reserved
    uint32_t PaddingMode : 3; // 0: No Padding, 1:PKCS7, 2:PaddingOneZeros, 3: PaddingZerosLen, 4:PaddingZeros; valid for ECB/CBC
    uint32_t KeySize : 2;  //0:128, 1:192, 2:256  
    uint32_t KeyType : 1;  //0: seruciry HW RNG, 1: Software key
    uint32_t Reserved0 : 7; 
    uint32_t Reserved1 : 16;  
}AesCtrl;

typedef struct AesStruct_Tag{
    uint32_t IVAddress;
    uint32_t InputData;
    uint32_t OutputData;
    uint32_t  KeyAddress;
    uint32_t DataLen;    
    AesCtrl Ctrl;
}AesStruct;

typedef enum _L2C_POWER_STATE {
  L2C_POWER_OFF,                        
  L2C_POWER_LOW,                        
  L2C_POWER_FULL                        
} L2C_POWER_STATE;

typedef struct _L2CAesResource{
    volatile L2CLccrFlashTlsReg* reg;
    L2CFlashTlsCfgReg *cfg;
    IRQn_Type irq_num;
    void (*irq_handler)(void);
    uint32_t init_mode;
    osSemaphoreId_t semL2cAes;
    uint32_t int_status;    
}L2CAesResource;

typedef struct {
    void (*Init)(void);
    int32_t (*Process)(AesStruct *);
    int32_t (*PowerControl) (L2C_POWER_STATE state, L2CAesResource *AesResourcePtr);              
    void (*DeInit)(void);
}L2CAesDriver;

L2CAesDriver * L2CGetFlashHandler(void);

#endif
