/*************************************************************************
	> File Name: parse_xml_bin.c
	> Author: 
	> Mail: 
	> Created Time: 2018年05月06日 星期日 23时44分03秒
 ************************************************************************/
#include "parse_xml_bin.h"

#ifndef EMBEDED_SYSTEM
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

#else

#include <typedef.h>
#include <log.h>
#include <libc.h>
#endif

__s32 find_view(const char * win_id, void * bin_data, view_table_item_t view_item);

__s32 check_magic(void * bin_data);
__s8 * eLIBs_strtok(__s8 *str, const __s8 *delim);


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

__s32 get_xml_num(void * bin_data)
{
	data_file_header_t header = (data_file_header_t) bin_data;
	return header->xml_num;
}

__s32 get_view_num(void * bin_data)
{
	data_file_header_t header = (data_file_header_t) bin_data;
	return header->view_num;
}

__s32 get_view_table_pos(void * bin_data)
{
	data_file_header_t header = (data_file_header_t) bin_data;
	return header->xml_view_table_pos;
}


void * get_property_item(const char * name, void * bin_data, view_table_item_t view_item)
{
	property_table_item_t property_item = NULL;
	__s32 i = 0;
	void * orig_bin_data = bin_data;
	
	if(view_item == NULL)
		return NULL;
	__s32 property_num = view_item->property_num;
	__s32 property_size = view_item->property_size;
	__s32 property_pos = view_item->property_pos;

	bin_data += property_pos;
	for(i = 0; i < property_num; i++)
	{
		property_table_item_nodata_t item = (property_table_item_nodata_t)bin_data;
		if(!strcmp(item->name, name))
		{
			printf("find the property : %s\n", item->name);

			property_item = (property_table_item_t)malloc(sizeof(struct property_table_item));
			if(property_item == NULL)
			{
				printf("alloc memory for property item failed\n");
				return NULL;
			}

			memcpy(property_item, item, sizeof(struct property_table_item_nodata));
			
			__s8 * property_data;

			if(property_item->data_type == DATA_TYPE_STRING)
				property_data = (__s8 *)malloc(sizeof(property_item->data_size+1));
			else
				property_data = (__s8 *)malloc(sizeof(property_item->data_size));
			
			if(property_data == NULL)
			{
				printf("alloc memory for property data failed!\n");
				return NULL;
			}

			memcpy(property_data, (orig_bin_data + property_item->data_pos),
							property_item->data_size);

			if(property_item->data_type == DATA_TYPE_STRING){
				*(property_data + property_item->data_size) = 0;
				printf("data = %s\n", property_data);
			}

			property_item->data = property_data;
			printf("property_item->data = %s\n", (__s8 *)property_item->data);

			return property_item;
		}
		bin_data += sizeof(struct property_table_item_nodata);

	}
	return NULL;
}


__s32 find_view(const char * win_id, void * bin_data, view_table_item_t view_item)
{
	__s32 view_num = 0;
	__s32 view_table_pos = 0;
	__s32 i = 0;

	if(view_item == NULL)
		return -1;
	data_file_header_t header = (data_file_header_t) bin_data;
	view_num = header->view_num;
	view_table_pos = header->xml_view_table_pos;


	bin_data += view_table_pos;
	for(i = 0; i < view_num; i++)
	{
		view_table_item_t item = (view_table_item_t)bin_data;
		if(!strcmp(item->view_id, win_id))
		{
			printf("find the view : %s\n", item->view_id);
			memcpy(view_item, item, sizeof(struct view_table_item));
			return 0;
		}
		bin_data += sizeof(struct view_table_item);
	}

	return -1;	
}

void * get_view_table_item(const char * win_id, void * bin_data)
{
	view_table_item_t item;
	__s32 ret = 0;

	item = (view_table_item_t)malloc(sizeof(struct view_table_item));
	if(item == NULL)
	{
		printf("alloc memory for view_table_item fail\n");
		return NULL;
	}

	ret = find_view(win_id, bin_data, item);
	if(ret == 0)
		return item;

	return NULL;
}

property_table_item_t parse_property_item(const char * win_id, const char * name, void * bin_data)
{
	view_table_item_t view_item;
	property_table_item_t property_item;

	view_item = get_view_table_item(win_id, bin_data);
	if(view_item == NULL)
		return NULL;
	
	property_item = get_property_item(name, bin_data, view_item);
	free(view_item);

	return property_item;
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
	fclose(fp);
    return bin_data;
}

void show_property_item(property_table_item_t item)
{
	if(item == NULL)
	{
		return;
	}
	printf("\n");
	printf("show the property item information\n");
	printf("property->name = %s\n", item->name);
	printf("property->data_size = %d\n", item->data_size);
	printf("property->data_pos = %d\n", item->data_pos);
	printf("property->data_type = %d\n", item->data_type);


	if(item->data_type == DATA_TYPE_STRING)
	{
		__s8 * data = (__s8 *)(item->data);
		printf("property->data = %s\n", data);
	}

	
	if(item->data_type == DATA_TYPE_INT_4)
	{
		__s32 * data = (__s32 *)(item->data);
		printf("property->data = %d\n", *data);

	}
}

__s8 * get_property_string_data(property_table_item_t item)
{
	if(item == NULL)
		return NULL;
	if(item->data_type == DATA_TYPE_STRING)
	{
		__s8 * data = (__s8 *)(item->data);
		printf("property->data = %s\n", data);
		return data;
	}
	return NULL;
}

__s32 get_property_int_data(property_table_item_t item)
{
	if(item == NULL)
		return NULL;
	if(item->data_type == DATA_TYPE_INT_4)
	{
		__s32 * data = (__s32 *)(item->data);
		printf("property->data = %d\n", *data);
		return *data;
	}
	return NULL;
}



__s32 get_bmp_array(property_table_item_t item, int array[], int num, int * err)
{
	__s32 i = 0;
	if(item->data_type == DATA_TYPE_STRING)
	{
		__s8 * data = (__s8 *)(item->data);
		printf("property->data = %s\n", data);
		show_property_item(item);
		char *p;
		p = eLIBs_strtok(data, ",");
		array[i] = atoi(p);
		i++;
    	while((p = eLIBs_strtok(NULL, ",")))
    	{
        	printf("%s ", p);
			array[i] = atoi(p);
			i++;
			
    	}
        printf("\n");
		*err = 0;
		return *err;
	}else{
		printf("data type error");
		*err = -1;
		return NULL;
	}
}

__s32 get_pos_array(property_table_item_t item, int array[][2], int num, int * err)
{
	__s32 i = 0;
	if(item->data_type == DATA_TYPE_STRING)
	{
		__s8 * data = (__s8 *)(item->data);
		printf("property->data = %s\n", data);
		show_property_item(item);
		char *p;
		p = eLIBs_strtok(data, ",");
		array[i][0] = atoi(p);
		p = eLIBs_strtok(data, ",");
        array[i][1] = atoi(p);
		i++;
    	while((p = eLIBs_strtok(NULL, ",")))
    	{
        	printf("%s ", p);
			array[i][0] = atoi(p);
            p = eLIBs_strtok(data, ",");
            array[i][1] = atoi(p);
			i++;
    	}
        printf("\n");
		*err = 0;
		return *err;
	}else{
		printf("data type error");
		*err = -1;
		return NULL;
	}
}

__s8 * eLIBs_strtok(__s8 *str, const __s8 *delim)
{
    static __s8 *src = NULL;                                      //记下上一次非分隔字符串字符的位置,详见图示
    const __s8 *indelim = delim;                                  //对delim做一个备份
    __s32 flag = 1,index = 0;                                

    //每一次调用strtok,flag标记都会使得程序只记录下第一个非分隔符的位置,以后出现非分隔符不再处理

    __s8 *temp = NULL;                                       //程序的返回值
 
    if(str == NULL)
    {
        str = src;                                               //若str为NULL则表示该程序继续处理上一次余下的字符串
    }
    for(; *str; str++)
    {
        delim = indelim;
		for(; *delim; delim++)
        {
			if(*str==*delim)
            {
                *str = NULL;                    //若找到delim中感兴趣的字符,将该字符置为NULL
                index = 1;                         //用来标记已出现感兴趣字符
                break;
            }
        }
        if(*str != NULL && flag == 1)
        {
            temp = str;                              //只记录下当前第一个非感兴趣字符的位置
            flag = 0;  
        }
            
		if(*str != NULL && flag == 0 && index == 1)
        {
			src = str;                                   //第二次出现非感兴趣字符的位置(之前一定出现过感兴趣字符)
            return temp;
		}
    }
    src = str;                              

     //执行该句表明一直未出现过感兴趣字符,或者说在出现了感兴趣的字符后,就没再出现过非感兴趣字符
    return temp;
}

#ifndef EMBEDED_SYSTEM
int main()
{
    int ret = 0;
    __s8 * bin_data;
    printf("begin parse xml data\n");

	char *test[]={ "win_id",   "unfocus_bmp",   "bmp_array", "pos_num", "pos_array"};
    
    __s8 * bin_path = "view_data";
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

	int i = 0;
	for(i = 0; i < sizeof(test)/sizeof(test[0]); i++)
	{
		property_table_item_t property_item = parse_property_item("home_win", test[i], bin_data);
		if(property_item != NULL)
		{
            show_property_item(property_item);	
		    free(property_item->data);
		    free(property_item);
    	    printf("\n");
		}
		else
        {
            printf("can not find the property [%s]  from [%s]\n", test[i], "home_win");
        }
	}
	
	free(bin_data);
    printf("\n");
    printf("parse xml data end\n");
	return 0;
}
#endif
