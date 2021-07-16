#include <stdio.h>
#include <string.h>
#include <json.h>
int main ()
{
    json_object *pobj = NULL;
    pobj = json_object_from_file("test.json");

    //1.json del
    json_object_object_del(pobj,"address");

    //2.save pobj to file
    json_object_to_file("test.json",pobj);
    json_object_put(pobj);

    return 0;
}