int oem_handler_multi_event(uint8* data_buf)
{
    json_object * object_web_data = NULL;
    json_object * object_jsonrpc = NULL;
    char *p_data;
    //p_data = data_buf+12;
    p_data = data_buf;
    object_web_data = json_tokener_parse(p_data);

    return 0;
}