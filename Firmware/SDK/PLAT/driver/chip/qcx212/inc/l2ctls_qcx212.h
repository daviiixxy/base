#ifndef __L2CSHA_H__
#define __L2CSHA_H__
typedef enum 
{
    L2C_SHA_TYPE_1 = 0,
    L2C_SHA_TYPE_224 = 1,
    L2C_SHA_TYPE_256 = 2,    
}L2CSHAType;

typedef enum 
{
    L2C_AES_MODE = 0,
    L2C_SHA_MODE = 1,
}L2CModeType;


typedef struct 
{
    uint32_t Encrypt : 1;  //0: Encrypt, 1:Decrypt
    uint32_t ChainMode : 2; //0:ECB, 1: CBC, 2/3:Reserved
    uint32_t PaddingMode : 3; // 0: No Padding, 1:PKCS7, 2:PaddingOneZeros, 3: PaddingZerosLen, 4:PaddingZeros; valid for ECB/CBC
    uint32_t KeySize : 2;  //0:128, 1:192
    uint32_t KeyType : 1;  //0: seruciry HW RNG, 1: Software key
    uint32_t Reserved0 : 7; 
    uint32_t Reserved1 : 16;  
}L2CTlsAesCtrl;

typedef struct L2CTlsAesStruct_Tag{
    uint32_t IVAddress;
    uint32_t InputData;
    uint32_t OutputData;
    uint32_t  KeyAddress;
    uint32_t DataLen;    
    uint32_t HeadLen;    
    L2CTlsAesCtrl Ctrl;
}L2CTlsAesStruct;



extern void L2CTlsInit(void);
extern int32_t L2CTlsCheckMode(L2CModeType ModeType, L2CSHAType ShaType);
extern void L2CShaComInit(L2CSHAType ShaType);
extern int32_t  L2CShaUpdate(uint32_t SrcAddr, uint32_t DstAddr, uint32_t Lenth, uint32_t LastFlag);
extern void L2CTlsDeInit(void);

extern int32_t  L2CTlsAesProcess(L2CTlsAesStruct *AESInfoPtr);


#define L2CTLSDRV_OK 0
#define L2CTLSDRV_BusyErr (-1)
#define L2CTLSDRV_UnsupportErr (-4)
#define L2CTLSDRV_ParameterErr (-5)


#define L2CShaInit L2CTlsInit
#endif
