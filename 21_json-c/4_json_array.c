#include <stdio.h>
#include <string.h>
#include <json-c/json.h>
int main ()
{
    //json_object *pobj = NULL;
    json_object *array = NULL;
    int i;
    //pobj = json_object_from_file("array.json");
    array = json_object_new_array();
    json_object_array_add(array,json_object_new_int(1));
    json_object_array_add(array,json_object_new_int(2));
    json_object_array_add(array,json_object_new_int(3));
    json_object_array_add(array,json_object_new_string("aaa"));
    json_object_array_add(array,json_object_new_string("bbb"));
    for(i=0; i< json_object_array_length(array); i++)
    {
        struct json_object *obj = json_object_array_get_idx(array,i);
        printf("i = %s\n",json_object_get_string(obj));
    }


    //2.save pobj to file
    json_object_to_file("test.json",array);
    json_object_put(array);

    return 0;
}