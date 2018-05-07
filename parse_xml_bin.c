/*************************************************************************
	> File Name: parse_xml_bin.c
	> Author: 
	> Mail: 
	> Created Time: 2018年05月06日 星期日 23时44分03秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h> 
#include "parse_xml_bin.h"


property_table_item_t get_prop_item(const char * win_id, const char * property_name, void * bin_data);

__s8 * load_bin(const char * path);

__s32 find_view(const char * win_id, void * bin_data, view_table_item_t view_item);

__s32 check_magic(void * bin_data);

__s32 check_magic(void * bin_data)
{
	data_file_header_t header = (data_file_header_t) bin_data;
	printf("magic = %s \nxml_num = %d \nview_num = %d \nxml_view_table_pos = %d\n",
					header->magic,
					header->xml_num,
					header->view_num,
					header->xml_view_table_pos);
	__s8 * magic = MAGIC;
	if(strcmp(header->magic, magic))
	{
		printf("check magic failed!\n");
		return -1;
	}
	return 0;
}

__s32 find_view(const char * win_id, void * bin_data, view_table_item_t view_item)
{
	return 0;	
}

__s8 * load_bin(const char * path)
{
    __s8 * bin_data = NULL;
    FILE *fp = fopen(path,"rb"); 
    if(!fp) 
        return 0; 
    fseek(fp,0L,SEEK_END); 
    int size=ftell(fp); 
    
    fseek(fp,0L,SEEK_SET);

    bin_data = (__s8 *)malloc(size);
    if(bin_data == NULL)
    {
        printf("malloc failed\n");
        return 0;
    }

    fread(bin_data, size, 1, fp);
    return bin_data;
}

int main()
{
    int ret = 0;
    __s8 * bin_data;
    printf("begin parse xml data\n");
    
    
    __s8 * bin_path = "view.data";
    bin_data = load_bin(bin_path);
    if(bin_data == 0)
    {
        printf("load_bin failed\n");
        return -1;
    }

	ret = check_magic(bin_data);
	if(ret != 0)
	{
		return -1;
	}

    printf("parse xml data end\n");
}
