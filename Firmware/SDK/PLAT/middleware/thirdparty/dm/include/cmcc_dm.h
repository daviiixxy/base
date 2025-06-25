#ifndef _OBJECT_DEFS_H_
#define _OBJECT_DEFS_H_

#include "cis_api.h"
#include "cis_internals.h"

//dm task
#define DM_TASK_STACK_SIZE (1024*2)

#define DM_SAMPLE_OBJECT_MAX              1
#define DM_SAMPLE_OID_A                   (666)
#define DM_SAMPLE_A_INSTANCE_COUNT        1
#define DM_SAMPLE_A_INSTANCE_BITMAP       "1"

#define CMCCDM_NVM_FILE_NAME      "cmccdmconfig.nvm"
#define DM_LOCATION_LEN  14

typedef enum
{
   APP_INIT_STATE,
   APP_DEACTIVE_STATE,
   APP_IPREADY_STATE,
   APP_REPORT_STATE,
   APP_IDLE_STATE
}dmRunningState_t;

typedef struct {
    BOOL bConnected;
    et_client_state_t pumpState;
	char location[DM_LOCATION_LEN+1];
} cmccDmRetentionContext;

typedef struct cmccDmNvmHeader_Tag
{
    UINT16 fileBodySize; //file body size, not include size of header;
    UINT8  version;
    UINT8  checkSum;
}cmccDmNvmHeader;

typedef struct {
    BOOL needRestore;
} dmCmdContext;


typedef struct dm_device_object
{
    cis_oid_t         oid;
    cis_instcount_t   instCount;
    const char*       instBitmap;
    const cis_rid_t*  attrListPtr;
    uint16_t          attrCount;
    const cis_rid_t*  actListPtr;
    uint16_t          actCount;
} dm_device_object;

//////////////////////////////////////////////////////////////////////////
//a object

typedef struct dm_object{
    int32_t intVal;
    float   floatVal;
    bool    boolVal;
    char    strVal[64];
    uint8_t update;
} dm_object;


typedef struct dm_instance
{
    cis_iid_t   instId;
    bool        enabled;
    dm_object instance;
} dm_instance;


enum{
    attributeA_deviceInfo     = 6601,
    attributeA_appInfo        = 6602,
    attributeA_MAC            = 6603,
    attributeA_ROM            = 6604,
    attributeA_RAM            = 6605,
    attributeA_CPU            = 6606,
    attributeA_sysVersion     = 6607,
    attributeA_softwareVer    = 6608,
    attributeA_softwareName   = 6609,
    attributeA_volte          = 6610,
    attributeA_netType        = 6611,
    attributeA_account        = 6612,
    attributeA_phoneNumber    = 6613,
    attributeA_location       = 6614,
};

enum{
    actionA_1           = 100,
};

                        
//at+mipldiscoverrsp=0,msgid1,1,69,"6601;6602;6603;6604;6605;6606;6607;6608;6609;6610;6611;6612;6613;6614" string bool integer
static const cis_rid_t const_AttrIds_a[] = {
    attributeA_deviceInfo,
    attributeA_appInfo,
    attributeA_MAC,
    attributeA_ROM,
    attributeA_RAM,
    attributeA_CPU,
    attributeA_sysVersion,
    attributeA_softwareVer,
    attributeA_softwareName,
    attributeA_volte,
    attributeA_netType,
    attributeA_account,
    attributeA_phoneNumber,
    attributeA_location,
};


static const cis_rid_t const_ActIds_a[] = {
    actionA_1,
};

typedef enum{
	DM_SAMPLE_CALLBACK_UNKNOWN = 0,
	DM_SAMPLE_CALLBACK_READ,
	DM_SAMPLE_CALLBACK_WRITE,
	DM_SAMPLE_CALLBACK_EXECUTE,
	DM_SAMPLE_CALLBACK_OBSERVE,
	DM_SAMPLE_CALLBACK_SETPARAMS,
	DM_SAMPLE_CALLBACK_DISCOVER,
}dm_callback_type_t;

struct dm_observe_info
{
    struct dm_observe_info* next;
    cis_listid_t    mid;
    cis_uri_t       uri;
    cis_observe_attr_t params;
};

struct dm_callback_info
{
    struct dm_callback_info* next;
    cis_listid_t       mid;
    dm_callback_type_t flag; 
    cis_uri_t          uri;

    union
    {
        struct  
        {
            bool flag;
        }toObserve;
        
        struct  
        {
            cis_observe_attr_t params;
        }toObserveParam;

        struct{
            uint8_t* buffer;
            uint32_t length;
        }toExec;
        
        struct{
            cis_data_t* value;
            cis_attrcount_t count;
        }toWrite;
    }param;
    
};

void cmccAutoRegisterInit(void);
//int dm_sample_dm_entry(MidWareDmConfig* config, BOOL needRestore);

#endif//_OBJECT_DEFS_H_

