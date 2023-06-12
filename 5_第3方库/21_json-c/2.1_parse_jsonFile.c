#include <stdio.h>
#include <string.h>
#include <json-c/json.h>

#define JSON_FILE "2.1_test.json"
int main ()
{
    json_object *pobj = NULL;
    json_object *ipv6_address_obj = NULL;
            json_object *address_obj = NULL;
            json_object *mask_obj = NULL;
    char address[64] = {0};
    int mask = 0;
    int i;

    pobj = json_object_from_file(JSON_FILE);
    ipv6_address_obj = json_object_object_get(pobj,"ipv6-address");
    printf ("13 ipv6: %s\n", json_object_to_json_string (ipv6_address_obj));

    //遍历数组
    for(i=0; i< json_object_array_length(ipv6_address_obj); i++)
    {
        struct json_object *obj = json_object_array_get_idx(ipv6_address_obj,i);
        printf("i = %s\n",json_object_to_json_string(obj));
        address_obj = json_object_object_get(obj,"address");
        mask_obj = json_object_object_get(obj,"mask");

        strncpy(address,json_object_get_string(address_obj),64);
        mask = json_object_get_int(mask_obj);
        printf("14 %s,mask=%d\n",address,mask);
    }

    //只需要释放 根obj即可
    //json_object_put(address_obj);
    //json_object_put(mask_obj);
    //json_object_put(ipv6_address_obj);
    json_object_put(pobj);

    return 0;
}
