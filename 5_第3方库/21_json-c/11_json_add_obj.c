#include <stdio.h>
#include <json-c/json.h>
/*
生成json 
{
  "name":"liuj ",
  "language":["china","English","French",123,456]
 }
*/
int main ()
{
    json_object *obj = json_object_new_object();
    json_object *name = NULL;
    json_object *language = NULL;

    //1.字符串 对象
    name = json_object_new_string ("liuj");

    //2.数组 对象
    language = json_object_new_array();
        json_object_array_add(language, json_object_new_string("china"));
        json_object_array_add(language, json_object_new_string("English"));
        json_object_array_add(language, json_object_new_string("French"));
        json_object_array_add(language, json_object_new_int(123));
        json_object_array_add(language, json_object_new_int(456));

    //3.将 字符串-数组 加到默认json中
    json_object_object_add(obj, "name", name);
    json_object_object_add(obj, "language", language);

    //5.生成文件
    json_object_to_file("test_add_base_obj.json", obj);

    //6.释放json obj
    json_object_put(name);
    json_object_put(language);
    json_object_put(obj);
}
