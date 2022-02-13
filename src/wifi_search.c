#include "wifi_search.h"

json_object * create_object(char * ssid_obj,char * ssid_val,char * pswd_obj,char * pswd_val){

    json_object *jobj = json_object_new_object();
    json_object *string_1 = json_object_new_string(ssid_val);
    json_object *string_2 = json_object_new_string(pswd_val);
    json_object_object_add(jobj,ssid_obj,string_1);
    json_object_object_add(jobj,pswd_obj,string_2);

    return jobj;
}

json_object * wifi_get_essid()
{
    FILE* cmd_file;
  	char cmd_to_snd[500];
  	char cmd_resp[100];
  	char essid[100];

    json_object *final_jobj = json_object_new_object();
    json_object *jarray = json_object_new_array();

    sprintf(cmd_to_snd, "sudo iw dev wlp6s0 scan | grep \"SSID\" | tr -d '\n'\n");
    cmd_file = popen(cmd_to_snd, "r");
    printf("%s",cmd_to_snd);
    fscanf(cmd_file, "%[^\n]", cmd_resp);
    pclose(cmd_file);

    char *tokenPointer = strtok(cmd_resp,"\t"); //remove tabs, replaced with NULL and made into tokens where tabs were previously present

    while(tokenPointer!=NULL)
    {
        printf("ssid: %s\n",tokenPointer+6);
        json_object_array_add(jarray,create_object("SSID",tokenPointer+6,"Password","pass"));
        tokenPointer = strtok(NULL,"\t");             //putting back the tabs in place of NULLs
    }

    json_object_object_add(final_jobj,"collection",jarray);

    return final_jobj;                      //return the array poiter
}
