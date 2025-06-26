#ifndef __EFUSE_H__
#define __EFUSE_H__
/**
\defgroup efuse_interface_gr Efuse Interface

\addtogroup efuse_interface_gr
\{
 */

/** \brief EFUSE status flag for read or burn operation */
typedef enum {
    EfuseStatIdle = 0x0, /**<Efuse read or burn operation idle */
    EfuseStatFail = 0x1,  /**<  Efuse read or burn operation fail */
    EfuseStatBurnSuccess = 0x2,  /**<  Efuse burn operation success */
    EfuseStatReadSuccess = 0x4,  /**<  Efuse read operation success */
    EfuseStatTimeOut = 0x8,    /**<  Efuse read or burn operation timeout */
}EfuseStatType;

/** \brief EFUSE BIT DEFINE [0-23] */
enum {
    EFUSE_CTRL_FLG_BYTELOC = 0,  /**<  start byte location of control flag field efuse bytes area */
    EFUSE_CTRL_DIS_BYTELOC = 1,  /**<  start byte location of control burn disable field efuse bytes area */
    EFUSE_HW_TRIM_BYTELOC = 2,  /**<  start byte location of ate trim field efuse bytes area */
    EFUSE_HW_DCXO_BYTELOC = 17,  /**<  start byte location of DCXO calib field efuse bytes area */
    EFUSE_HW_PLAT_BYTELOC = 18,  /**<  start byte location of platform field efuse bytes area */
    EFUSE_HW_AES_BYTELOC = 24,    /**<  start byte location of aes key field efuse bytes area */
    EFUSE_SW_APP_BYTELOC = 48,    /**<  start byte location of software app field efuse bytes area */
    EFUSE_SW_ECDSA_BYTELOC = 64,   /**<  start byte location of software ecdsa field efuse bytes area */ 
    EFUSE_LIMIT_BITS_BYTELOC = 128, /**<  end efuse byte location */ 
};

/** \brief EFUSE FILED LENGTH DEFINE [0-23] */
enum {
    EFUSE_CTRL_FLG_BYTELEN = 1, /**<  byte length of control flag field efuse bytes area */
    EFUSE_CTRL_DIS_BYTELEN = 1, /**<  byte length of control burn disable field efuse bytes area */
    EFUSE_HW_TRIM_BYTELEN = 15, /**<  byte length of ate trim field efuse bytes area */
    EFUSE_HW_DCXO_BYTELEN = 1, /**<  byte length of DCXO calib field efuse bytes area */
    EFUSE_HW_PLAT_BYTELEN = 6, /**<  byte length of platform field efuse bytes area */
    EFUSE_HW_AES_BYTELEN = 24, /**<  byte length of aes key field efuse bytes area */   
    EFUSE_SW_APP_BYTELEN= 80,  /**<  byte length of software app field efuse bytes area */   
    EFUSE_SW_ECDSA_BYTELEN = 64,  /**<  byte length  of software ecdsa field efuse bytes area */ 
    EFUSE_LIMIT_BITS_BYTELEN = 128,  /**<  total length  of all efuse bytes area */ 
};

/** \brief EFUSE Burn Code */
#define EFUSE_CTRL_FLG_BURNCODE  0xABCD0123  /**<  burn code for control flag field efuse bytes area */
#define EFUSE_CTRL_DIS_BURNCOD  0xABCD0123   /**<  burn code for control disable field efuse bytes area */
#define EFUSE_HW_TRIM_BURNCOD  0xABCD0369    /**<  burn code for ate trim field efuse bytes area */
#define EFUSE_HW_DCXO_BURNCOD  0xABCD0482   /**<  burn code for DCXO calib field efuse bytes area */
#define EFUSE_HW_PLAT_BURNCOD  0xABCD1111    /**<  burn code for platform field efuse bytes area */
#define EFUSE_HW_AES_BURNCOD  0xABCD0246  /**<  burn code for aes key field efuse bytes area */
#define EFUSE_SW_APP_BURNCOD  0xABCD0000   /**<  burn code for software app and software ecdsa field efuse bytes area */  

/** \brief EFUSE area part number */
enum {
    EFUSE_CTRL_FLG_PARTNO = 0,
    EFUSE_CTRL_DIS_PARTNO = 1,
    EFUSE_HW_TRIM_PARTNO = 2,
    EFUSE_HW_DCXO_PARTNO = 3,
    EFUSE_HW_PLAT_PARTNO = 4,
    EFUSE_HW_AES_PARTNO = 5,    
    EFUSE_SW_APP_PARTNO = 6,        // vvvvv
    EFUSE_MAX_PART_NUM = 7
};

/** \brief Part info element in defined efuse fields table */
typedef struct {
    uint8_t PartId; /**<part id  */
    uint8_t PartLoc; /**<start bytes location of part */
    uint8_t PartLen; /**<bytes length of part */
    uint8_t Rsv;
    uint32_t BurnCode; /**<EFUSE Burn Code for part */
}EFUSEBitsPartInfo;

#define EFUSE_MAX_POR_REG_CNT 6   /**<macro for por reg idx */  
#define EFUSE_MAX_POLL_CNT 7000  /**<macro for poll count*/  
#define EFUSE_MAX_POLL_DELAY_US (1000*8)  /**<macro for poll timeout ,more than 512bits *0.9us*/

/** \brief EFUSE Controller General Register */
typedef struct {
    uint32_t PClkEn :  1; /**<internal apb clk en, 38.4MHz */
    uint32_t FClkEn : 1; /**<internal function clk, fclk en, 38.4MHz */
    uint32_t SClkEn : 1; //internal function slow clk for burn, 38.4/32->1.2MHz
    uint32_t Rsv0   :  1;
    uint32_t AutoCgEn : 1; //internal clock auto clock gating enable;
    uint32_t Rsv1 :  27;
}EFUSE_CGR;

/*
#define BURN_KEY_CTRL 0xABCD0123
#define BURN_KEY_TRIM 0xABCD0369
#define BURN_KEY_DCX0 0xABCD0482
#define BURN_KEY_PLAT 0xABCD1111
#define BURN_KEY_AES 0xABCD0246
#define BURN_KEY_SW 0xABCD0000*/
/** \brief Control Code Register,  see EFUSE Burn Code*/
typedef struct {
    uint32_t CtrlCode;  
}EFUSE_CCR;

/** \brief EFUSE IP Control Reigster */
typedef struct {
    uint32_t PdSw : 1;  /**<efuse power down control for software read and burn */  
    uint32_t PdRd : 1; /**<internal v1.1 power down, read only*/  
    uint32_t Pass : 1; /**<internal v1.8 pass, read only */  
    uint32_t Csb : 1; /**< read only */  
    uint32_t Load : 1; /**< read only */  
    uint32_t PgEnb : 1; /**< read only */  
    uint32_t Stb : 1; /**< read only */  
    uint32_t Rsvd7 : 1; /**< read only */  
    uint32_t EfuseA : 10; /**< read only */  
    uint32_t Rsvd18_23 : 6; /**< read only */  
    uint32_t EfuseQ : 8; /**< read only */  
}EFUSE_ICR;

//efuse por read
/** \brief POR Read Trigger/Status Register*/
typedef struct{
    uint32_t Rsv0 : 8;
    uint32_t ReadBusy0 : 1;/**<por0 trg efuse read busy flag, set if por0 trg accepted, clr if por0 trg finsih, for DCXO filed */
    uint32_t ReadBusy1 : 1;/**<por1 trg efuse read busy flag, set if por1 trg accepted, clr if por1 trg finsih, for CTRL/TRIM/PLAT/AES field */
    uint32_t ReadFinish0 : 1;/**<por0 trg efuse read finish flag, clr if por0 trg accepted, set if por0 trg finish */
    uint32_t ReadFinish1 : 1;/**<por1 trg efuse read finish flag, clr if por1 trg accepted, set if por1 trg finish */
    uint32_t Rsv12_15 : 4;
    uint32_t ReadFail0 : 2; /**<por read trg0 fail flag, clr if por0 trg, set if por0 failed, [0]por0 read trg when read_busy, [1]por0 read trg when burn_busy */
    uint32_t ReadFail1 : 2; /**<por read trg1 fail flag, clr if por1 trg, set if por0 failed, [0]por1 read trg when read_busy, [1]por1 read trg when burn_busy */
    uint32_t Rsv20_31 : 12;
}EFUSE_PRSR;

/** \brief Bits define for control flag field efuse byte*/
typedef struct {
    uint8_t BurnTest : 1;
    uint8_t BurnFlagTrim : 1;
    uint8_t BurnFlagDcxo : 1;
    uint8_t BurnFlagPlat : 1;
    uint8_t BurnFlagAes : 1;
    uint8_t BurnFlagSw  : 1;
    uint8_t Rsvd : 2;
}CtrlFlagBits;

/** \brief Bits define for control disable field efuse byte*/
typedef struct {
    uint8_t BurnDis : 1;
    uint8_t BurnDisTrim : 1;
    uint8_t BurnDisDCXO : 1;
    uint8_t BurnDisPlat : 1;
    uint8_t BurnDisAes : 1;
    uint8_t BurnDisSw : 1;
    uint8_t Rsvd : 2;
}CtrlDisBits;

/** \brief Bytes define for ate trim field efuse bytes 0_1*/
typedef struct {
    uint8_t DataArr[2];
}HWTrimByte0_1;

/** \brief Bytes define for ate trim field efuse bytes 2_5*/
typedef struct {
    uint8_t DataArr[4];
}HWTrimByte2_5;

/** \brief Bytes define for ate trim field efuse bytes 6_9*/
typedef struct {
    uint8_t DataArr[4];
}HWTrimByte6_9;

/** \brief Bytes define for ate trim field efuse bytes 10_13*/
typedef struct {
    uint8_t DataArr[4];
}HWTrimByte10_13;

/** \brief Bytes define for ate trim field efuse byte 14*/
typedef struct {
    uint8_t Data;
}HWTrimByte14;

/** \brief Bytes define for dcxo field efuse byte*/
typedef struct {
    uint8_t Data;
}HWDCXO;

/** \brief Bits define for platform field efuse byte*/
typedef struct {
    uint8_t JtagDis : 1;
    uint8_t SecurityBootEn : 1;
    uint8_t DebugDis : 1;
    uint8_t DownloadDis : 1;
    uint8_t Rsv : 4;
}HWPlatBits;

/** \brief Efuse bytes info in PRDR0, bytes 0-3*/
typedef struct 
{
    CtrlFlagBits CtrlFlag;
    CtrlDisBits CtrlDis;
    HWTrimByte0_1 HwTrim0_1;
}EFUSE_PRDR0;

/** \brief Efuse bytes info in PRDR1, bytes 4-7*/
typedef struct 
{
    HWTrimByte2_5 HwTrim2_5;
}EFUSE_PRDR1;

/** \brief Efuse bytes info in PRDR2, bytes 8-11*/
typedef struct 
{
    HWTrimByte6_9 HwTrim6_9;
}EFUSE_PRDR2;

/** \brief Efuse bytes info in PRDR3, bytes 12-15*/
typedef struct 
{
    HWTrimByte10_13 HwTrim10_13;
}EFUSE_PRDR3;

/** \brief Efuse bytes info in PRDR4, bytes 16-19*/
typedef struct 
{
    HWTrimByte14 HwTrim14;
    HWDCXO HwDxco;
    HWPlatBits HwPlat;
    uint8_t Rsv;
}EFUSE_PRDR4;

/** \brief Efuse bytes info in PRDR5, bytes 20-23*/
typedef struct 
{
    uint8_t RsvArr[4];
}EFUSE_PRDR5;

//efuse sw read
/** \brief SW Read Control Register*/
typedef struct {
    uint32_t ReadByteAddr : 7;  /**<  read byte addr 0, 127 */
    uint32_t Rsv7_15 : 9;
    uint32_t ReadByteLenSub1 : 3;  /**< read byte len sub 1 , max64/8 = 8 [0,7]*/
    uint32_t Rsv20_30 : 12;
    uint32_t ReadEnable : 1;  /**< Enable sw read ,just for software trigger */
}EFUSE_SRCR;

/** \brief SW Read Trigger/Status Register*/
typedef struct {
    uint32_t ReadTrg : 1; /**<  read sw trg, write 1 to trg. */
    uint32_t Rsv1_7 : 7;
    uint32_t ReadBusy : 1; /**<  sw trg efuse read busy flag, set if sw trg accepted, clr if sw trg inish*/
    uint32_t ReadFinish : 1;/**<sw trg efuse read busy flag, clr if sw trg accepted, set if sw trg inish*/
    uint32_t Rsv10_15 : 6;
    uint32_t ReadFail :  3;/**<hould be 0 if read_trg accepted, [0] sw read when read_busy, [1] sw read when burn_busy, [2] read invalid region aes*/
    uint32_t Rsv19_31 : 13;
}EFUSE_SRSR;

/** \brief SW Read Fuse Data/Content0 Register*/
typedef struct {
    uint32_t Data;
}EFUSE_SRDR0;

/** \brief SW Read Fuse Data/Content1 Register*/
typedef struct {
    uint32_t Data;
}EFUSE_SRDR1;

//efuse sw burn
/** \brief SW Burn Control Register*/
typedef struct {
    uint32_t BurnBitAddr : 10; /**<  sw burn bit address [0,1023] */ //to be fixed? should byte address? need align ?
    uint32_t Rsv10_15 : 6 ;
    uint32_t BurnByteLen : 6 ;/**<  sw burn byte len sub 1, max 64/8=8, [0,7] */
    uint32_t Rsv20_29 : 8;
    uint32_t BurnType : 1; /**<  sw burn trg type , 0 : normal, 1: just aes from rng */
    uint32_t BurnEnable :1;/**<  sw burn enable*/
}EFUSE_SBCR;

/** \brief SW Burn Trigger/Status Register*/
typedef struct {
    uint32_t BurnTrg : 1;/**< sw burn trg write 1 to trg */
    uint32_t Rsv1_7 : 7;
    uint32_t BurnBusy : 1;/**<sw burn trg busy flag, set if sw/hw trg accpeted, clr if sw/hw trg finish */
    uint32_t BurnFinish : 1;/**<sw burn finish flag, clr if sw/hw trg accpeted, set if sw/hw trg finish*/
    uint32_t Rsv10_15 : 6;
    //clr when swtrg, should be 0 when swtrg accepted, [0] sw burn when burn busy, [1] sw burn when read_busy, [2]sw burn befor por_read_finish, 
    //[3]  sw burn after burn_disable, [4] sw aes burn before RNG Ready, [5] sw aes burn after burn disable aes
    uint32_t BurnFail : 6; /**<sw burn fail err code*/
    uint32_t Rsv22_31 : 10;
}EFUSE_SBSR;

/** \brief SW Burn Data/Content0 Register*/
typedef struct {
    uint32_t Data;
}EFUSE_SBDR0;

/** \brief SW Burn Data/Content1 Register*/
typedef struct {
    uint32_t Data;
}EFUSE_SBDR1;

//TBD, EFUSE overwrite registers, OWSR, OWDR0-3
/** \brief Efuse controller Registers*/
typedef struct {
    __IO EFUSE_CGR CGR;  /**<EFUSE Controller General Register */
    __IO EFUSE_CCR CCR; /**<EFUSE Control Code Register*/
    __IO uint32_t RsvWord2;
    __IO EFUSE_ICR ICR;    
    __IO EFUSE_PRSR PRSR; /**<POR Read Trigger/Status Register*/
    __IO uint32_t RsvWord5;    
    __IO EFUSE_PRDR0 PRDR0;
    __IO EFUSE_PRDR1 PRDR1;
    __IO EFUSE_PRDR2 PRDR2;
    __IO EFUSE_PRDR3 PRDR3;   
    __IO EFUSE_PRDR4 PRDR4;
    __IO EFUSE_PRDR5 PRDR5;     
    __IO EFUSE_SRCR SRCR;    /**<SW Read Control Register*/
    __IO EFUSE_SRSR SRSR;    /**<SW Read Trigger/Status Register*/
    __IO EFUSE_SRDR0 SRDR0;/**<SW Read Fuse Data/Content0 Register*/
    __IO EFUSE_SRDR1 SRDR1; /**<SW Read Fuse Data/Content1 Register*/
    __IO uint32_t RsvWord16; //For ATE Burn status
    __IO uint32_t RsvWord17; //    
    __IO EFUSE_SBCR SBCR;    /**<SW Burn Control Register*/
    __IO EFUSE_SBSR SBSR;    /**<SW Burn Trigger/Status Register*/
    __IO EFUSE_SBDR0 SBDR0;/**<SW Burn Data/Content0 Register*/
    __IO EFUSE_SBDR0 SBDR1; /**<SW Burn Data/Content Register*/
}EFUSEReg;

/**

  \fn    void EfuseInit(void);
  \brief Init efuse module, enable clk for efuse
 */
extern void EfuseInit(void);

/**
  \fn    void EfuseDeInit(void);
  \brief Deinit efuse module, disable clk for efuse
 */
extern void EfuseDeInit(void);

extern const EFUSEBitsPartInfo * GetBurnPartInfo(uint32_t PartId);

extern int32_t EFusePORRead(uint32_t Idx, uint32_t *PData);

/**
  \fn    void EFuseSWRead(uint8_t ByteLoc, uint8_t ByteLen, uint8_t *PBuff);
  \brief Software Read efuse bits value 
  \param[in] ByteLoc    Byte location of efuse bits to read
  \param[in] ByteLen     Byte length of efuse bits to read, should less or equal than 8
  \param[out] PBuff   Output buffer for efuse bits value
  \return Efuse read result status, EFUSEDRV_OK(0) success, otherwise fail

  \code
  Example to set read efuse plat bits, byte location 18, bits7:0
  HWPlatBits tHWPlatBits;
  mask = SaveAndSetIRQMask();
  EfuseInit();  
  RetValue = EFuseSWRead(EFUSE_HW_PLAT_BYTELOC, 1, (uint8_t*)(&tHWPlatBits));
  EfuseDeInit();   
  RestoreIRQMask(mask);
  

  Example to set read efuse control flag bits, byte location 0, bits7:0
  CtrlFlagBits tCtrlFlagBits; 
  mask = SaveAndSetIRQMask();
  EfuseInit();
  RetValue = EFuseSWRead(EFUSE_CTRL_FLG_BYTELOC, 1, ((uint8_t*)tCtrlFlagBits));
  EfuseDeInit();  
  RestoreIRQMask(mask);
  
  \endcode  
 */
extern int32_t EFuseSWRead(uint8_t ByteLoc, uint8_t ByteLen, uint8_t *PBuff);
extern int32_t EFuseCtrlFlagRead(CtrlFlagBits *CtrlFlagBitsPtr);
/**
  \fn    int32_t EFuseSWReadSafePolling(uint8_t ByteLoc, uint8_t ByteLen, uint8_t *PBuff);
  \brief Software Read efuse bits value with int masked
  \param[in] ByteLoc    Byte location of efuse bits to read
  \param[in] ByteLen     Byte length of efuse bits to read, should less or equal than 8
  \param[out] PBuff   Output buffer for efuse bits value
  \return Efuse read result status, EFUSEDRV_OK(0) success, otherwise fail
*/
extern int32_t EFuseSWReadSafePolling(uint8_t ByteLoc, uint8_t ByteLen, uint8_t *PBuff);
extern int32_t EFusePORPlatBitsRead(HWPlatBits *PlatBitsPtr);
extern int32_t EFuseSwReadEccPubkey(uint8_t *PBuff);
extern int32_t EFuseSwPlatBitsRead(HWPlatBits *SWPlatBitsPtr);

#define EFUSERegPtr ((EFUSEReg*) (EFUSE_BASE_ADDR))

#define EFUSEDRV_OK 0
#define EFUSEDRV_PORReadErr (-1)
#define EFUSEDRV_ReadErr (-2)
#define EFUSEDRV_BurnErr (-3)
#define EFUSEDRV_TimeOutErr (-4)
#define EFUSEDRV_LocErr (-5)
#define EFUSEDRV_LenErr (-6)
#define EFUSEDRV_MutexLockErr (-7)

/** \} */


#endif
