#ifndef __L2C_QCX212_H__
#define __L2C_QCX212_H__

#include <stdio.h>
#include "string.h"
#include "qcx212.h"
#include "pad_qcx212.h"

#define L2C_REG_BASE_ADDR   (0x47020000)
#define L2C_LCCR_REG_ADDR    L2C_REG_BASE_ADDR

#define L2C_LCCR_FLASH_REG_ADDR    (L2C_REG_BASE_ADDR+0x68)
#define L2C_LCCR_TLS_REG_ADDR    (L2C_REG_BASE_ADDR+0x70)

/*************************************************************
    *   L2CLccr Reg
    *   L2C Data Operation Configuration Registers (L2C Lccr)
*************************************************************/

//L2C FLASH TLS module 
typedef struct FlashTlsCfgCtrl_Tag{
    uint32_t Lenth : 16;  //max 2^16 -1
    uint32_t AlgMode : 1; //0:AES, 1:SHA
    uint32_t Dir : 1;  //0: Encrypt, 1:Decrypt
    uint32_t AesMode : 2; //0:ECB, 1: CBC, 2/3:Reserved
    uint32_t PaddingMode : 3; // 0: No Padding, 1:PKCS7, 2:PaddingOneZeros, 3: PaddingZerosLen, 4:PaddingZeros; valid for ECB/CBC
    uint32_t CKlenB0 : 1; //Key Len, combine B1,B0
    uint32_t CKlenB1 : 1; //Key Len,combine B1,B0  , 0:128, 1:192, 2:256    , for aes
    uint32_t ShaMode : 2; //0: sha1, 1-sha224, 2-sha256
    uint32_t ShaBLS : 1; //Selects SHA output Endianity, 0: little endian, 1: big endian
    uint32_t RCS : 1; //0:no rcs, last data, padding 1:rcs, pdate data, no padding
    uint32_t OutEn: 1; //0:Not output digest, 1:Output digest, only valid when RCS= 1
    uint32_t Reserved : 2;
}FlashTlsCfgCtrl;


typedef struct IAHeadLen_Tag
{
    uint16_t HeadLen;
    uint16_t Reserved;
}IAHeadLen;

typedef union {
    IAHeadLen HeadInfo;
    uint32_t VectorAddress;
}IAInfo;

typedef struct L2CFlashTlsCfgReg_Tag{
    union FirstWord{
        uint32_t HeadAddress; // for tls sha mode 
        uint32_t CKAAddress; //for  tls aes mode
        uint32_t Reserved; //for flash aes mode
    }u;
    uint32_t SrcAddr;
    uint32_t DstAddr;
    FlashTlsCfgCtrl Ctrl;
    IAInfo IA;
}L2CFlashTlsCfgReg;

typedef struct FlashTlsTrg_Tag{
  uint32_t Cfg : 1;  // bit 0: 0-stop, 1-trig, when stop auto clear to 0 ,read always 0
  uint32_t Busy : 1; //bit 0: idle, 1:active; will be set to 1 when set cfg= 1, finish task return to 0 
  uint32_t Reserved: 30;
}FlashTlsTrg;

typedef struct L2CLccrFlashTlsReg_Tag{
    uint32_t BaseAddr;
    FlashTlsTrg Trig;
}L2CLccrFlashTlsReg;

#define L2CLccrTlsRegPtr ((volatile L2CLccrFlashTlsReg*)(L2C_LCCR_TLS_REG_ADDR))
#define L2CLccrFlashRegPtr ((volatile L2CLccrFlashTlsReg*)(L2C_LCCR_FLASH_REG_ADDR))

#define L2CDRV_OK 0
#define L2CDRV_BusyErr (-1)
#define L2CDRV_UnsupportErr (-4)
#define L2CDRV_ParameterErr (-5)

#endif
