#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <json-c/json.h>

int main (int argc, char **argv)
{
    char json_string[]="{ \"glossary\": { \"title\": \"example glossary\", \"pageCount\": 100}}";
	struct json_object *new_obj, * glossary, *page_obj;
	int pageCount;
    new_obj = json_tokener_parse(json_string);
	printf ("11 name=%s\n", json_object_to_json_string (new_obj));

	glossary = json_object_object_get (new_obj, "glossary");
	printf ("12 title=%s\n", json_object_to_json_string (glossary));

	page_obj = json_object_object_get (glossary, "pageCount");
	pageCount = json_object_get_int (page_obj);
	printf ("13 Page count = %d\n", pageCount);

	json_object_put (new_obj);
	return 0;
}
