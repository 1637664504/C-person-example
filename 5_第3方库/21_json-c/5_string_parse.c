#include <stdio.h>
#include <string.h>
#include <json-c/json.h>
int main ()
{
    //char buf[128]="{\"name\":\"John Johnson\",\"age\":123}";
    char buf[128]="{\"method\": \"MultiWan\",\"params\": {\"link\":\"eth1\", \"status\":222}}";
    json_object * pobj;
    json_object *pobj_poarams = NULL;
    json_object *pobj_link = NULL;
    json_object *pobj_status = NULL;

#if test
    pobj = json_tokener_parse(buf);
    pobj_poarams = json_object_object_get(pobj,"params");
    pobj_link = json_object_object_get(pobj_poarams,"link");
    pobj_status = json_object_object_get(pobj_poarams,"status");
#else
    pobj = json_tokener_parse(buf);
    //pobj_poarams = json_object_object_get(pobj,"params");
    pobj_link = json_object_object_get(pobj,"link");
    pobj_status = json_object_object_get(pobj,"status");
#endif    

    printf("%s %d\n",json_object_get_string(pobj_link),json_object_get_int(pobj_status));

    //json_object_put(name);
    //json_object_put(age);
    json_object_put(pobj);

    return 0;
}
