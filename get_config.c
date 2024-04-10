#include "get_config.h"

char* get_dns_addr(char* filename){
    FILE* conf_file;
    char* variable = NULL;
    size_t variable_size = 0;
    char variable_name[18], variable_value[16];
    char* result = NULL;
    
    conf_file = fopen(filename, "r");
    
    if(errno){
        printf("%s\n", strerror(errno));
    }else{
        while(getline(&variable, &variable_size, conf_file) != -1){
            if(sscanf(variable, "%[^=]=%[^\n]", variable_name, variable_value) == 2){
                if(strncmp(variable_name, "UPSTREAM_DNS_ADDR", 17) == 0){
                    result = (char*)malloc(strlen(variable_value) + 1);
                    strcpy(result, variable_value);
                }
            }
        }
    }

    if(variable) free(variable);

    if(conf_file) fclose(conf_file);

    return result;
}

int get_response_type(char* filename){
    FILE* conf_file;
    char* variable = NULL;
    size_t variable_size = 0;
    char variable_name[16], variable_value[8];
    int result = 0;
    
    conf_file = fopen(filename, "r");
    
    if(errno){
        printf("%s\n", strerror(errno));
    }else{
        while(getline(&variable, &variable_size, conf_file) != -1){
            if(sscanf(variable, "%[^=]=%[^\n]", variable_name, variable_value) == 2){
                if(strncmp(variable_name, "RESPONSE_BANNED", 15) == 0){
                    result = atoi(variable_value);
                }
            }
        }
    }

    if(variable) free(variable);

    if(conf_file) fclose(conf_file);

    return result;
}

char* get_blacklist(char* filename){
    FILE* conf_file;
    char* variable = NULL;
    size_t variable_size = 0;
    char variable_name[18];
    char* variable_value = NULL;
    char* result = NULL;
    
    conf_file = fopen(filename, "r");
    
    if(errno){
        printf("%s\n", strerror(errno));
    }else{
        while(getline(&variable, &variable_size, conf_file) != -1){
            variable_value = malloc(strlen(variable));
            if(sscanf(variable, "%[^=]=%[^\n]", variable_name, variable_value) == 2){
                if(strncmp(variable_name, "BLACKLIST", 9) == 0){
                    result = (char*)malloc(strlen(variable_value) + 1);
                    strcpy(result, variable_value);
                }
            }

            if(variable_value) free(variable_value);
        }
    }

    if(variable) free(variable);

    if(conf_file) fclose(conf_file);

    return result;
}
