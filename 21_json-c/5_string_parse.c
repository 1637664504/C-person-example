#include <stdio.h>
#include <string.h>
#include <json-c/json.h>
int main ()
{
    char buf[128]="{\"name\":\"John Johnson\",\"age\":123}";
    json_object *pobj = NULL;
    json_object *name = NULL;
    json_object *age = NULL;

    pobj = json_tokener_parse(buf);

    name = json_object_object_get(pobj,"name");
    age = json_object_object_get(pobj,"age");
    
    printf("%s %s\n",json_object_get_string(name),json_object_get_string(age));

    //json_object_put(name);
    //json_object_put(age);
    json_object_put(pobj);
    

    return 0;
}
