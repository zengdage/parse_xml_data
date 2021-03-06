/*************************************************************************
	> File Name: parse_xml_bin.h
	> Author: zengzhijin
	> Mail: zengkings@foxmail.com
	> Created Time: 2018年05月06日 星期日 23时24分57秒
 ************************************************************************/

#ifndef _PARSE_XML_BIN_H
#define _PARSE_XML_BIN_H

//#define EMBEDED_SYSTEM

#define MAGICLEN 8
#define MAGIC "view666"

#define VIEW_ID_LEN  16
#define PROPERTY_NAME_LEN  32
#define XML_NAME_LEN  16


#ifndef EMBEDED_SYSTEM
typedef int __s32;
typedef unsigned int __u32;
typedef char  __s8;
typedef unsigned char  __u8;


#else

#include <typedef.h>
#include <syscall.h>
#include <sys_mem.h>

#define FILE ES_FILE

#define printf eLIBs_printf
#define malloc(x) esMEMS_Malloc(0,x)
#define free(x)   esMEMS_Mfree(0,x)
#define memcpy    eLIBs_memcpy
#define memset    eLIBs_memset
#define strcmp    eLIBs_strcmp
#define fopen     eLIBs_fopen
#define fseek     eLIBs_fseek
#define fread     eLIBs_fread
#define fclose    eLIBs_fclose
#define ftell    eLIBs_ftell
#define atoi     eLIBs_atoi

#endif


#define DATA_TYPE_INT_4   1
#define DATA_TYPE_FLOAT_4 2
#define DATA_TYPE_LONG_8  3
#define DATA_TYPE_CHAR_1  4
#define DATA_TYPE_SHORT_2 5
#define DATA_TYPE_DOUBLE_4 6
#define DATA_TYPE_STRING   7

#define TypeBasewin   1
#define TypeButton    2
#define TypeCtrwin    3
#define TypeFrmwin    4
#define TypeGmsgBox   5
#define TypeIconMenu  6
#define TypeListMenu  7
#define TypeMainwin   8
	  
#define TypeMsgBox    9
#define TypeProgBar   10
#define TypeProgSheet 11
#define TypeSIcons    12
#define TypeSLider    13
#define TypeSListBox  14
#define TypeSpinBox   15
	  
#define TypeStatic    16
#define TypeTxtBox    17
#define TypeWin       18


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


struct view {
	__s8   id[VIEW_ID_LEN];
	__s32  view_type;
	struct view * parent_view;
	struct view * child_views;    
	struct view * brother_views;    
	__s32  status;
	void * data;
    __s32 (* precreate_hook)(void *data1, void * data2);
};
typedef struct view * view_t;


struct xml_item {
	__s8 name [XML_NAME_LEN];
	__s32 view_num;
	__s32 view_item_pos;
};
typedef struct xml_item * xml_item_t;

#ifndef EMBEDED_SYSTEM
struct root_para {

};
typedef struct root_para * root_para_t;
#endif

struct create_win
{
	__s32 win_type;
	void (*create_win_function)(view_t view_tree, 
			view_table_item_t item);
};

__s32 get_root_para(void * bin_data, root_para_t para);
view_t search_view_tree(view_t view_tree, const char * name);

void * get_property_item(const char * name, void * bin_data, view_table_item_t view_item);
property_table_item_t parse_property_item(const char * xml_name, const char * win_id, const char * name, void * bin_data);
__s8 * get_property_string_data(property_table_item_t item);
__s8 * load_bin(const char * path);

__s32 get_property_int_data(property_table_item_t item, __s32 * err);
__s32 get_bmp_array(property_table_item_t item, int array[] , int num, int * err);

__s32 get_pos_array(property_table_item_t item, int array[][2] , int num, int * err);
#endif

