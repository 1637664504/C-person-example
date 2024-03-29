#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <json-c/json.h>

int main (int argc, char **argv)
{
	struct json_object *new_obj;
	int pageCount;
    //new_obj = json_tokener_parse("/* more difficult test case */ { \"glossary\": { \"title\": \"example glossary\", \"pageCount\": 100, \"GlossDiv\": { \"title\": \"S\", \"GlossList\": [ { \"ID\": \"SGML\", \"SortAs\": \"SGML\", \"GlossTerm\": \"Standard Generalized Markup Language\", \"Acronym\": \"SGML\", \"Abbrev\": \"ISO 8879:1986\", \"GlossDef\": \"A meta-markup language, used to create markup languages such as DocBook.\", \"GlossSeeAlso\": [\"GML\", \"XML\", \"markup\"] } ] } } }");
	new_obj = json_tokener_parse("{ \"glossary\": { \"title\": \"example glossary\", \"pageCount\": 100}}");
	printf ("11 new_obj.to_string()=%s\n", json_object_to_json_string (new_obj));

	new_obj = json_object_object_get (new_obj, "glossary");
	printf ("12 new_obj.to_string()=%s\n", json_object_to_json_string (new_obj));

	new_obj = json_object_object_get (new_obj, "pageCount");
	pageCount = json_object_get_int (new_obj);
	printf ("13 Page count = %d\n", pageCount);

	json_object_put (new_obj);
	return 0;
}
