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

__s32 find_view(const char * xml_view, const char * win_id, void * bin_data, view_table_item_t view_item);
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

view_t search_view_tree(view_t view_tree, const char * name)
{
	view_t temp = NULL;
        if(!strcmp(view_tree->id, name))
	{
		return view_tree;
	}
	else
	{
		if(view_tree->child_views != NULL)
	        {
		        temp = search_view_tree(view_tree->child_views, name);
		}

		if(temp != NULL)
			return temp;

		view_t temp_brother = view_tree->brother_views;
		for(; temp_brother != NULL; )
		{
			temp = search_view_tree(temp_brother, name);
			if(temp != NULL)
				return temp;
			temp_brother = temp->brother_views;
		}
	}
	return temp;
}

__s32 get_xml_table_pos(void * bin_data)
{
	data_file_header_t header = (data_file_header_t) bin_data;
	return header->xml_view_table_pos;
}

__s32 get_root_para(void * bin_data, root_para_t para)
{
    __s32 ret = 0;
    
    property_table_item_t item;
    //TODO
    item = parse_property_item("root_para.xml", "root_para", "xxx", bin_data);
    if(item == NULL)
        return -1;


    return ret; 

}


__s32 pre_create_win_hook(view_t view, view_table_item_t item)
{
    __s32 ret = 0;
    if(view->precreate_hook != NULL)
        return view->precreate_hook(view, item);
    return ret;
}

void create_win_func_basewin(view_t view, view_table_item_t item)
{
    pre_create_win_hook(view, item);
}

void create_win_func_button(view_t view, view_table_item_t item)
{
    pre_create_win_hook(view, item);
}
void create_win_func_ctrwin(view_t view, view_table_item_t item)
{
    pre_create_win_hook(view, item);

}
void create_win_func_frmwin(view_t view, view_table_item_t item)
{
    pre_create_win_hook(view, item);

}
void create_win_func_gmsgbox(view_t view, view_table_item_t item)
{
    pre_create_win_hook(view, item);

}
void create_win_func_iconmenu(view_t view, view_table_item_t item)
{
    pre_create_win_hook(view, item);

}
void create_win_func_listmenu(view_t view, view_table_item_t item)
{
    pre_create_win_hook(view, item);

}
void create_win_func_mainwin(view_t view, view_table_item_t item)
{
    pre_create_win_hook(view, item);
    printf("win create %s\n", __FUNCTION__);
}
void create_win_func_msgbox(view_t view, view_table_item_t item)
{
    pre_create_win_hook(view, item);

}
void create_win_func_progbar(view_t view, view_table_item_t item)
{
    pre_create_win_hook(view, item);

}
void create_win_func_progsheet(view_t view, view_table_item_t item)
{
    pre_create_win_hook(view, item);

}
void create_win_func_sicons(view_t view, view_table_item_t item)
{
    pre_create_win_hook(view, item);

}
void create_win_func_slider(view_t view, view_table_item_t item)
{
    pre_create_win_hook(view, item);

}
void create_win_func_slistbox(view_t view, view_table_item_t item)
{
    pre_create_win_hook(view, item);

}
void create_win_func_spinbox(view_t view, view_table_item_t item)
{
    pre_create_win_hook(view, item);

}
void create_win_func_static(view_t view, view_table_item_t item)
{
    pre_create_win_hook(view, item);

}
void create_win_func_txtbox(view_t view, view_table_item_t item)
{
    pre_create_win_hook(view, item);

}
void create_win_func_win(view_t view, view_table_item_t item)
{
    pre_create_win_hook(view, item);

}



struct create_win create_win_array[] = {
	{TypeBasewin, create_win_func_basewin},
	{TypeButton, create_win_func_button},
	{TypeCtrwin, create_win_func_ctrwin},
	{TypeFrmwin, create_win_func_frmwin},
	{TypeGmsgBox, create_win_func_gmsgbox},
	{TypeIconMenu, create_win_func_iconmenu},
	{TypeListMenu, create_win_func_listmenu},
	{TypeMainwin, create_win_func_mainwin},
	{TypeMsgBox, create_win_func_msgbox},
	{TypeProgBar, create_win_func_progbar},
	{TypeProgSheet, create_win_func_progsheet},
	{TypeSIcons, create_win_func_sicons},
	{TypeSLider, create_win_func_slider},
	{TypeSListBox, create_win_func_slistbox},
	{TypeSpinBox, create_win_func_spinbox},
	{TypeStatic, create_win_func_static},
	{TypeTxtBox, create_win_func_txtbox},
	{TypeWin,create_win_func_win},
};

__s32 create_win(view_t view, view_table_item_t item)
{
	__s32 type = 0;
	__s32 i = 0;
	type = item->type;
	for(i = 0; i < sizeof(create_win_array)/sizeof(create_win_array[0]); i++)
	{
		if(type == create_win_array[i].win_type){
		    printf("type = %d, win_type = %d", type, create_win_array[i].win_type);
			create_win_array[i].create_win_function(view, item);
			break;
		}
	}
}



void create_view_tree(view_t view, void * bin_data, int * num)
{	
	view_table_item_t item = (view_table_item_t)(bin_data + sizeof(struct view_table_item) * (*num));
	__s32 i = 0;
	__s32 subchild_num = item->direct_subchild_item_num;

	view->view_type = item->type;
	memcpy(view->id, item->view_id, VIEW_ID_LEN);

	create_win(view, item);
	view_t sub_view_first = NULL;
	view_t sub_view_save = NULL;

	for(i = 0; i < subchild_num; i++)
	{	
		sub_view_first = (view_t)malloc(sizeof(struct view));
		if(sub_view_first == NULL)
		{
			printf("alloc memory for sub view failed!\n");
			return;
		}
		memset(sub_view_first, 0, sizeof(struct view));
		
		if(i == 0)
		{
			view->child_views = sub_view_first;
		}
		else
		{
			view_t temp = view;
			if(temp->child_views == NULL)
			{
				temp->child_views = sub_view_first;
			}
			else
			{
				temp = view->child_views;
				for(; temp->brother_views != NULL; )
				{
					temp = temp->brother_views;
				}
				temp->brother_views = sub_view_first;
			}
		}


		sub_view_first->parent_view = view;
		sub_view_save = sub_view_first;
		*num = (*num) + 1;
		create_view_tree(sub_view_first, bin_data, num);

	}
	if(view->child_views != NULL)
		printf("child: %s\n", view->child_views->id);
}

void show_view_tree(view_t view)
{
	printf("\n");
	if(view->parent_view != NULL)
		printf("the view [%s] parent_view is [%s]\n", view->id, view->parent_view->id);
	
	if(view->view_type != 0)
		printf("the view [%s] view_type is [%d]\n", view->id, view->view_type);
	
	if(view->brother_views != NULL)
	{
		printf("the view [%s] brother_view is [%s]->", view->id, view->brother_views->id);
		view_t temp = view->brother_views;
		for(; temp->brother_views != NULL; )
		{
			temp = temp->brother_views;
			printf("[%s]->", temp->id);
		}
		printf("\n");
	}

	if(view->child_views != NULL)
	{
		printf("the view [%s] child_view is [%s,%d]->", view->id, view->child_views->id, view->child_views->view_type);
		view_t temp = view->child_views;
		for(; temp->brother_views != NULL; )
		{
			temp = temp->brother_views;
			printf("[%s,%d]->", temp->id, temp->view_type);
		}
		printf("\n");
		
		temp = view->child_views;
		for(; temp != NULL; )
		{
			show_view_tree(temp);
			temp = temp->brother_views;
			if(temp == NULL)
				break;
		}
		printf("\n");

	}
	printf("\n");


}


__s32 get_view_tree(const char * xml_name, void * bin_data, view_t views)
{
	__s32 i = 0;
	__s32 view_table_i = 0;
	__s32 xml_num = 0;
	__s32 xml_table_pos = 0;
	__s32 view_pos = 0;
	__s32 view_num = 0;
	void * orig_data = bin_data;
	
	data_file_header_t header = (data_file_header_t) bin_data;
	xml_num = header->xml_num;
	xml_table_pos = header->xml_view_table_pos;
	
	bin_data += xml_table_pos;


	xml_item_t item = NULL;
	for(i = 0; i < xml_num; i++)
	{
		item = (xml_item_t)bin_data;
		if(!strcmp(item->name, xml_name))
		{
			printf("find the xml file [%s]\n", item->name);
			break;
		}
		bin_data += sizeof(struct xml_item);
	}

	if(item == NULL)
		return -1;

	bin_data = orig_data;
	view_pos = item->view_item_pos;
	view_num = item->view_num;

	bin_data += view_pos;
		
	memset(&views[i], 0, sizeof(struct view));
	create_view_tree(views, bin_data, &view_table_i);

	show_view_tree(views);

	return 0;

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
			//printf("property_item->data = %s\n", (__s8 *)property_item->data);

			return property_item;
		}
		bin_data += sizeof(struct property_table_item_nodata);

	}
	return NULL;
}


__s32 find_view(const char * xml_name, const char * win_id, void * bin_data, view_table_item_t view_item)
{
	__s32 xml_num = 0;
	__s32 view_num = 0;
	__s32 xml_table_pos = 0;
	__s32 view_table_pos = 0;
	void * orig_data = bin_data;
	__s32 i = 0;

	if(view_item == NULL)
		return -1;
	data_file_header_t header = (data_file_header_t) bin_data;
	xml_num = header->xml_num;
	xml_table_pos = header->xml_view_table_pos;
	
	bin_data += xml_table_pos;
	xml_item_t item = NULL;
	for(i = 0; i < xml_num; i++)
	{
		item = (xml_item_t)bin_data;
		if(!strcmp(item->name, xml_name))
		{
			printf("find the xml file [%s]\n", item->name);
			break;
		}
		bin_data += sizeof(struct xml_item);
	}

	if(item == NULL)
		return -1;

	bin_data = orig_data;
	view_table_pos = item->view_item_pos;
	view_num = item->view_num;
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

void * get_view_table_item(const char * xml_name, const char * win_id, void * bin_data)
{
	view_table_item_t item;
	__s32 ret = 0;

	item = (view_table_item_t)malloc(sizeof(struct view_table_item));
	if(item == NULL)
	{
		printf("alloc memory for view_table_item fail\n");
		return NULL;
	}

	memset(item, 0, sizeof(struct view_table_item));
	ret = find_view(xml_name, win_id, bin_data, item);
	if(ret == 0)
		return item;

	return NULL;
}

property_table_item_t parse_property_item(const char * xml_name, const char * win_id, const char * name, void * bin_data)
{
	view_table_item_t view_item;
	property_table_item_t property_item;

	view_item = get_view_table_item(xml_name, win_id, bin_data);
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

	memset(bin_data, 0, size);
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

__s32 get_property_int_data(property_table_item_t item, __s32 * err)
{
	if(item == NULL)
    {
        *err = -1;
		return 0;
    }
	if(item->data_type == DATA_TYPE_INT_4)
	{
        *err = 0;
		__s32 * data = (__s32 *)(item->data);
		printf("property->data = %d\n", *data);
		return *data;
	}
    *err = -2;
	return 0;
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
		return *err;
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
		return 0;
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
                *str = 0;                    //若找到delim中感兴趣的字符,将该字符置为NULL
                index = 1;                         //用来标记已出现感兴趣字符
                break;
            }
        }
        if(*str != 0 && flag == 1)
        {
            temp = str;                              //只记录下当前第一个非感兴趣字符的位置
            flag = 0;  
        }
            
		if(*str != 0 && flag == 0 && index == 1)
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
    __s32 ret = 0;
    __s8 * bin_data;
	__s32 xml_table_pos = 0;
	__s32 xml_num = 0;

	__s32 i = 0;
    
	printf("begin parse xml data\n");

	__s8 *test[]={ "win_id",   "unfocus_bmp",   "bmp_array", "pos_num", "pos_array"};
    
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

	for(i = 0; i < sizeof(test)/sizeof(test[0]); i++)
	{
		property_table_item_t property_item = parse_property_item("home.xml","home_win", test[i], bin_data);
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

	xml_num = get_xml_num(bin_data);
	xml_table_pos = get_xml_table_pos(bin_data);

	struct view v;
	get_view_tree("home.xml", bin_data, &v);
	
	free(bin_data);

	view_t temp = search_view_tree(&v, "main1");
	if(temp == NULL)
		printf("search homw_win failded!\n");
	else
		printf("search the view [%s] success!\n", temp->id);

        printf("\n");
        printf("parse xml data end\n");
	return 0;
}
#endif
