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
    json_object *pobj_aaa = NULL;

    pobj = json_tokener_parse(buf);
    if(json_object_object_get_ex(pobj,"params",&pobj_poarams))
    {
        int ret1,ret2,ret3;
        ret1= json_object_object_get_ex(pobj_poarams,"link",&pobj_link);
        ret2 = json_object_object_get_ex(pobj_poarams,"status",&pobj_status);
        ret3 = json_object_object_get_ex(pobj_poarams,"aaa",&pobj_aaa);
        printf("%d %d %d\n",ret1,ret2,ret3);
    }

    printf("%s %d\n",json_object_get_string(pobj_link),json_object_get_int(pobj_status));

    //json_object_put(name);
    //json_object_put(age);
    json_object_put(pobj);

    return 0;
}
