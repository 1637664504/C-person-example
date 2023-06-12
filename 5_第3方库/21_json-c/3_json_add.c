#include <stdio.h>
#include <string.h>
#include <json.h>
int main ()
{
    json_object *pobj = NULL;
    pobj = json_object_from_file("test.json");

    //1.json add
    json_object_object_add(pobj,"address",json_object_new_string("Shen Zhen"));
    json_object_object_add(pobj,"high",json_object_new_int(172));

    //2.save pobj to file
    json_object_to_file("test.json",pobj);
    json_object_put(pobj);

    return 0;
}