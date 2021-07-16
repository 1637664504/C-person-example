#include <stdio.h>
#include <string.h>
#include <json.h>
int main ()
{
    json_object *pobj = NULL;
    json_object *name_obj = NULL;
    enum json_type type;
    char val[64] = {0};

    pobj = json_object_from_file("test.json");
    name_obj = json_object_object_get(pobj,"name");
    type = json_object_get_type(name_obj);
    if(type == json_type_string)
        //val = json_object_get_string(name_obj);
        strncpy(val,json_object_get_string(name_obj),64);
    printf("name=%s, val=%s\n","name",val);

    //int类型
    json_object *age_obj = NULL;
    int age = 0;

    age_obj = json_object_object_get(pobj,"age");
    type = json_object_get_type(age_obj);
    if(type == json_type_int)
        age = json_object_get_int(age_obj);
    printf("age=%d\n",age);

    json_object_put(pobj);
    json_object_put(age_obj);
    json_object_put(name_obj);

    return 0;
}
