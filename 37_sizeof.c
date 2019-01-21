#include<stdio.h>

#ifndef INC_BTRM_BOOT
#define INC_BTRM_BOOT         0
#endif
#define NVRAM_BOOTLDR_SIG_LEN           256
#define NVRAM_CV_KEY_LEN                514
#define NVRAM_ENC_KEY_LEN               32

#define NVRAM_BOOTLINE_LEN              256
#define NVRAM_BOARD_ID_STRING_LEN       16
#define NVRAM_MAC_ADDRESS_LEN           6
#define NVRAM_GPON_SERIAL_NUMBER_LEN    13
#define NVRAM_GPON_PASSWORD_LEN         11
#define NVRAM_WLAN_PARAMS_LEN      256
#define NVRAM_WPS_DEVICE_PIN_LEN   8
#define NP_BOOT             0
#define NP_ROOTFS_1         1
#define NP_ROOTFS_2         2
#define NP_DATA             3
#define NP_BBT              4
#define NP_TOTAL            5
#define BCM_MAX_EXTRA_PARTITIONS 4
#define NAND_FULL_PARTITION_SEARCH  0
#define NVRAM_TENDA_LEN			20

struct allocs_dhd {
    unsigned char dhd_size[3];
    unsigned char reserved;
};

struct allocs_rdp {
    unsigned char param1_size;
    unsigned char param2_size;
    unsigned char reserved[2];
};

typedef struct
{
    unsigned int ulVersion;
    char szBootline[NVRAM_BOOTLINE_LEN];
    char szBoardId[NVRAM_BOARD_ID_STRING_LEN];
    unsigned int ulMainTpNum;
    unsigned int ulPsiSize;
    unsigned int ulNumMacAddrs;
    unsigned char ucaBaseMacAddr[NVRAM_MAC_ADDRESS_LEN];
    char pad;
    char backupPsi;  /**< if 0x01, allocate space for a backup PSI */
    unsigned int ulCheckSumV4;
    char gponSerialNumber[NVRAM_GPON_SERIAL_NUMBER_LEN];
    char gponPassword[NVRAM_GPON_PASSWORD_LEN];
    char wpsDevicePin[NVRAM_WPS_DEVICE_PIN_LEN];
    char wlanParams[NVRAM_WLAN_PARAMS_LEN];
    unsigned int ulSyslogSize; /**< number of KB to allocate for persistent syslog */
    unsigned int ulNandPartOfsKb[NP_TOTAL];
    unsigned int ulNandPartSizeKb[NP_TOTAL];
    char szVoiceBoardId[NVRAM_BOARD_ID_STRING_LEN];
    unsigned int afeId[2];
    unsigned short opticRxPwrReading;   // optical initial rx power reading
    unsigned short opticRxPwrOffset;    // optical rx power offset
    unsigned short opticTxPwrReading;   // optical initial tx power reading
    unsigned char ucUnused2[58];
    unsigned char ucFlashBlkSize;
    unsigned char ucAuxFSPercent;
    unsigned char ucUnused3[2];
    unsigned int ulBoardStuffOption;   // board options. bit0-3 is for DECT    
    union {
        unsigned int reserved;
        struct allocs_rdp alloc_rdp;
    } allocs;
    unsigned int ulMemoryConfig;
    struct partition_info {
	/*
		2MSB represent the 
			00 = MB 
			01 = GB
			10 = reserved
			11 = reserved
		14LSB represent multiple of 2MSB
	*/
	
	unsigned short size;
    } part_info[BCM_MAX_EXTRA_PARTITIONS];
    struct allocs_dhd alloc_dhd;

    /* Add any new non-secure related elements here */
# define NVFEAT_AVSDISABLED  (1<<0)     // bit indicating avs should be disabled
# define NVFEAT_RESERVED    (1<<31)     // bit reserved for erasure detection
    unsigned int ulFeatures;            // feature bitmask
    char RFTestFlag[NVRAM_TENDA_LEN];		    /* add for ate 2018/1/16 */
    char ThroughputTestFlag[NVRAM_TENDA_LEN];	/* add for ate 2018/1/16 */
    char FinishTestFlag[NVRAM_TENDA_LEN];		/* add for ate 2018/1/16 */
    char SerialNumber[NVRAM_TENDA_LEN];		/* add for ate 2018/1/16 */
    char wpsPin[NVRAM_TENDA_LEN];	/* add for ate 2018/1/16 */
    char Ssid[NVRAM_TENDA_LEN];			/* add for ate 2018/1/16 */
    char Wpa_Pw[NVRAM_TENDA_LEN];		/* add for ate 2018/1/16 */
    char Country[NVRAM_TENDA_LEN];		/* add for ate 2018/1/16 */
    char Channel[NVRAM_TENDA_LEN];		/* add for ate 2018/1/16 */
    int factoryflag;   				/* add for ate 2018/1/16 */
    char chUnused[84]; /* Adjust chUnused such that everything above + chUnused[] + ulCheckSum = 1k */

#if (INC_BTRM_BOOT==1) && (defined(_BCM963268_) || defined(CONFIG_BCM963268))
    unsigned int ulCheckSum_1k;
    char signature[NVRAM_BOOTLDR_SIG_LEN];
    char mfgCvKey[NVRAM_CV_KEY_LEN];
    char opCvKey[NVRAM_CV_KEY_LEN];
    char bek[NVRAM_ENC_KEY_LEN];
    char iek[NVRAM_ENC_KEY_LEN];
    char biv[NVRAM_ENC_IV_LEN];
    char iiv[NVRAM_ENC_IV_LEN];
    /* Add any secure boot related elements here */
    char chSecUnused[632];
#endif

    unsigned int ulCheckSum;
} NVRAM_DATA, *PNVRAM_DATA;

int main()
{
	printf("%u \n",sizeof(NVRAM_DATA));
	
}


