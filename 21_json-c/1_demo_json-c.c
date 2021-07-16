#include <stdio.h>
#include <json.h>
int
main ()
{
  int ret;
  //(1)创建
  //创建一个空的json对象
  json_object *j_NullObj = NULL;
  //创建字符串型的json对象
  json_object *j_str = json_object_new_string ("test string ");
  //创建一个数组对象
  json_object *j_array = json_object_new_array ();
  //给元素添加到数组末尾
  json_object_array_add (j_array, json_object_new_string ("china"));
  json_object_array_add (j_array, json_object_new_string ("English"));
  json_object_array_add (j_array, json_object_new_string ("Australia"));
  json_object_array_add (j_array, json_object_new_string ("French"));

  //将上面创建的对象加入到json对象j_cfg中
  json_object *j_cfg = json_object_new_object();
  json_object_object_add (j_cfg, "str1", j_str);
  json_object_object_add (j_cfg, "array1", j_array);
  #if 0
  //打印j_cfg
  printf ("j_cfg:%s", json_object_to_json_string (j_cfg));
  //（2）修改
  //修改Autralia为Korea,在实际中需要搜索Autralia的位置idx，这个改变传染到了j_cfg
  json_object_array_put_idx (j_array, 2, json_object_new_string ("korea"));
  //删除French
  json_object_array_put_idx (j_array, 3, NULL);

  printf ("j_cfg:%s", json_object_to_json_string (j_cfg));
  //（3）将j_cfg保存在project的根目录下的文件jcfg.dat中，该文件没有则新建，
  //有则销毁重新写入
  #endif
  //(4)free
  json_object_to_file ("jcfg.dat", j_cfg);
  json_object_put (j_str);
  json_object_put (j_array);
  //json_object_get(j_cfg);
  //json_object_put (j_cfg);
  printf("1111\n");
}
