/*************************************************************************
	> File Name: parse_xml_bin.h
	> Author: zengzhijin
	> Mail: zengkings@foxmail.com
	> Created Time: 2018年05月06日 星期日 23时24分57秒
 ************************************************************************/

#ifndef _PARSE_XML_BIN_H
#define _PARSE_XML_BIN_H

//#define EMED 

#define MAGICLEN 8
#define MAGIC "view666"

#define VIEW_ID_LEN  16
#define PROPERTY_NAME_LEN  32

#ifndef EMED
typedef int __s32;
typedef unsigned int __u32;
typedef char  __s8;
typedef unsigned char  __u8;


#else

#define FILE ES_FILE

#define printf eLIBs_printf
#define malloc(x) esMEMS_Malloc(0,x)
#define free(x)   esMEMS_Mfree(x)
#define memcpy    eLIBs_memcpy
#define strcmp    eLIBs_strcmp
#define fopen     eLIBs_fopen
#define fseek     eLIBs_fseek
#define fread     eLIBs_fread
#define fclose     eLIBs_fclose
#endif


#define DATA_TYPE_INT_4   1
#define DATA_TYPE_FLOAT_4 2
#define DATA_TYPE_LONG_8  3
#define DATA_TYPE_CHAR_1  4
#define DATA_TYPE_SHORT_2 5
#define DATA_TYPE_DOUBLE_4 6
#define DATA_TYPE_STRING   7


struct data_file_header {
    __s8  magic [MAGICLEN];
    __s32 xml_num;
    __s32 view_num;
    __s32 xml_view_table_pos;
};

typedef struct data_file_header * data_file_header_t;

struct view_table_item {
    __s8 view_id [VIEW_ID_LEN];
    __s32 type;
    __s32 direct_subchild_item_num;
    __s32 all_subchild_item_num;
    __s32 property_num;
    __s32 property_size;
    __s32 property_pos;
};
typedef struct view_table_item * view_table_item_t;


struct property_table_item {
    __s8 name [PROPERTY_NAME_LEN];
    __s32 data_size;
    __s32 data_pos;
    __s32 data_type;
    void * data;
};
typedef struct property_table_item * property_table_item_t;

struct property_table_item_nodata {
    __s8 name [PROPERTY_NAME_LEN];
    __s32 data_size;
    __s32 data_pos;
    __s32 data_type;
};
typedef struct property_table_item_nodata * property_table_item_nodata_t;

#endif

