#define JRD_NO_ERROR 0
#define JRD_FAIL     1
#define JRD_DATA_PACKAGE_DIR "~/config"

typedef enum{
    /*secssion getSMSStoreState*/
    E_PARAM_U8 = 0,
    E_PARAM_BOOL,
    E_PARAM_U16,
    E_PARAM_INT,
    E_PARAM_U32,
    E_PARAM_U64,
    E_PARAM_I64,
    E_PARAM_STR,
    E_PARAM_ENUM,
    E_PARAM_NULL,
    E_PARAM_F32,
    E_PARAM_OBJECT, // Connie add for json parser, 2014/8/12
    E_PARAM_OBJECT_DATA,
    E_PARAM_ARRAY_DATA,
    E_PARAMTYPE_MAX,
}e_jrd_paramtype_type;

static int jrd_data_set_config_dir(struct uci_context *ctx,char *package_name)
{
    int ret = JRD_NO_ERROR;
    boolean jrd_package = FALSE;

    if(!package_name || !ctx)
    {
        printf("Error, Input paramer is null. \n");
        return JRD_FAIL;
    }

    uci_set_confdir(ctx,JRD_DATA_PACKAGE_DIR);

    return ret;
}

static int  __jrd_data_update_value(char *package_name,char *section_name, char *option_name, void *value, e_jrd_paramtype_type type)
{
    struct uci_context *ctx = NULL;
    struct uci_ptr ptr ={0};
    char uci_value[256] = {0};
    int ret = 0;
    int uci_ret = UCI_OK;
    
    if(!package_name || !section_name || !option_name || !value)
    {
        printf("Error, Input paramer is null. \n");
        return JRD_FAIL;
    }
    ctx = uci_alloc_context();
    if(!ctx)
    {
        printf("Error, alloc context fail. \n");
        return JRD_FAIL;
    }
    jrd_data_set_config_dir(ctx,package_name);
    ptr.package = package_name;
    ptr.section = section_name;
    ptr.option = option_name;
    switch(type)
    {
        case  E_PARAM_U8:
            JRD_SNPRINTF(uci_value,JRD_DATA_UCI_VALUE_MAX,"%d",*((uint8*)value));
            break;
        case  E_PARAM_BOOL:
            JRD_SNPRINTF(uci_value,JRD_DATA_UCI_VALUE_MAX,"%d",*((boolean*)value));
            break;
        case E_PARAM_INT:
        case E_PARAM_ENUM:
            JRD_SNPRINTF(uci_value,JRD_DATA_UCI_VALUE_MAX,"%d",*((int*)value));
            break;
        case E_PARAM_U64:
            JRD_SNPRINTF(uci_value,JRD_DATA_UCI_VALUE_MAX,"%llu",*((uint64*)value));
            break;
        case E_PARAM_STR:
            JRD_SNPRINTF(uci_value,JRD_DATA_UCI_VALUE_MAX,"%s",(char*)value);
            break;
        default :
            printf("Error, param_type:%d \n",  type);
            break;
    }
    ptr.value = uci_value;

    if (section_name[0] == '@' && strchr(section_name, '[') && strchr(section_name, ']'))
    {
        ptr.flags |= UCI_LOOKUP_EXTENDED;
        if (uci_lookup_ptr(ctx, &ptr, NULL, true) != UCI_OK)
        {
            ret = JRD_FAIL;
            goto op_free_buffer;
        }
    }

    uci_ret = uci_set(ctx, &ptr);
    if(uci_ret != UCI_OK)
    {
        ret = JRD_FAIL;
        goto op_free_buffer;
    }
    uci_ret = uci_save(ctx,ptr.p);
    if(uci_ret != UCI_OK)
    {
        ret = JRD_FAIL;
        goto op_free_buffer;
    }

op_free_buffer:
    if(ptr.p)
        uci_unload(ctx, ptr.p);
    uci_free_context(ctx);
    return ret;
}

static int __jrd_data_commit_package(char *package_name)
{
    struct uci_context *ctx = NULL;
    struct uci_ptr ptr ={0};
    int ret = JRD_NO_ERROR;
    int uci_ret = UCI_OK;

    if(!package_name)
    {
        printf("Error, Input paramer is null. \n");
        return JRD_FAIL;
    }
    ctx = uci_alloc_context();
    if(!ctx)
    {
        printf("Error, alloc context fail. \n");
        return JRD_FAIL;
    }
    jrd_data_set_config_dir(ctx,package_name);
    if (uci_lookup_ptr(ctx, &ptr, package_name, true) != UCI_OK)
    {
        ret = JRD_FAIL;
        goto op_free_buffer;
    }
    uci_ret = uci_commit(ctx, &ptr.p, false);	
    if(uci_ret != UCI_OK)
    {
        ret = JRD_FAIL;
        goto op_free_buffer;
    }

op_free_buffer:
    if(ptr.p)
        uci_unload(ctx, ptr.p);
    uci_free_context(ctx);
    return ret;
}

int main(void)
{
    char config[16]="network";
    char section[16]="wan2";
    
    __jrd_data_update_value(config,section,"ifname","eth1",E_PARAM_STR,4);
    __jrd_data_commit_package(config);
}