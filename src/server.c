#include "civetweb.h"
#include <json-c/json.h>
#include <string.h>
#include "wifi_search.h"


int handleMessage(struct mg_connection *conn, const char * method, const char * uri){

  int handleSuccess=0;

  if(!strcmp(method,"POST") && !strcmp(uri, "/postdata")){
      handleSuccess = handlePostText(conn,uri);
      return handleSuccess;
    }

  if(!strcmp(method,"POST") && !strcmp(uri, "/postjson")){
      fprintf(stderr, "Inside if\n");
      handleSuccess = handlePostJson(conn,uri);
      return handleSuccess;
    }

  if(!strcmp(method,"GET") && !strcmp(uri, "/getjson")){
      handleSuccess = handleGetJson(conn,uri);
      return handleSuccess;
    }
  }


int handlePostText(struct mg_connection *conn, const char * uri){

  char data[200], resp[200], input1[sizeof(data)], input2[sizeof(data)];
  int data_len;

  data_len = mg_read(conn, data, sizeof(data));

  mg_get_var(data, data_len, "a", input1, sizeof(input1));
  mg_get_var(data, data_len, "b", input2, sizeof(input2));

  sprintf(resp,"The data retreived is a:%s and b:%s\n", input1, input2);
  fprintf(stderr,"RespString:%s\n",resp);

  mg_send_http_ok(conn, "text/plain", sizeof(resp));
  if(mg_write(conn, resp, sizeof(resp)) == -1)
  {
    fprintf(stderr,"Failure in handlePostText\n");
  }
  else{
    fprintf(stderr,"Success in handlePostText\n");
  }
}


int handleGetJson(struct mg_connection *conn, const char * uri){

  const char * send_string;
  json_object * rcv_object = wifi_get_essid();
  send_string = json_object_get_string(rcv_object);

  mg_send_http_ok(conn, "application/json; charset=utf-8", (int) strlen(send_string));

  if(mg_write(conn, send_string, (int) strlen(send_string)) == -1)
  {
    fprintf(stderr,"Failure in handleGetJson\n");
  }
  else{
    fprintf(stderr,"Success in handleGetJson\n");
  }
}


int handlePostJson(struct mg_connection *conn, const char * uri){

  char cmd_to_wifi[100];
  FILE* fp;
  char data[1024];
  char resp[1024];
  struct json_object *parsed_json;
  struct json_object *a_object;
  struct json_object *b_object;

  fprintf(stderr, "Inside Post Json\n");

  mg_read(conn, data, sizeof(data));
  parsed_json = json_tokener_parse(data);
  json_object_object_get_ex(parsed_json, "SSID", &a_object);
  json_object_object_get_ex(parsed_json, "password", &b_object);

  sprintf(resp,"input_ssid: %s input_pass: %s\n",json_object_get_string(a_object), json_object_get_string(b_object));
  fprintf(stderr, "%s\n",resp );

  sprintf(cmd_to_wifi, "nmcli dev wifi connect '%s' password '%s'",json_object_get_string(a_object),json_object_get_string(b_object));
  fp = popen(cmd_to_wifi, "r");
	fprintf("cmd_to_wifi: %s",cmd_to_wifi);
	pclose(fp);

  mg_send_http_error(conn,204,"%s","");
}


static int begin_request_handler(struct mg_connection *conn){
    int handleState=0;
    const struct mg_request_info *ri = mg_get_request_info(conn);

    fprintf(stderr,"\n\nUri:%s\n",ri->local_uri);
    fprintf(stderr,"Method type:%s\n",ri->request_method);
    fprintf(stderr,"Query string:%s\n",ri->query_string);

    handleMessage(conn, ri->request_method, ri->local_uri);

    //minimum requirement for begin_request_handler to operate
    if(ri->query_string != 0){
      fprintf(stderr,"Query received:%s\n",ri->query_string);
    }
}


void main(){
  struct mg_context *ctx;
  struct mg_callbacks callbacks;

  const char *options[] = {
      "listening_ports", "8080",
      "document_root", "../docroot",
      NULL
    };

  //const char *options[] = {"listening_ports", "8080", NULL};
  memset(&callbacks, 0, sizeof(callbacks));
  callbacks.begin_request = begin_request_handler;

  ctx = mg_start(&callbacks, NULL, options);

  printf("Server started on port(s) %s with web root [%s]\n",
        mg_get_option(ctx, "listening_ports"),
         mg_get_option(ctx, "document_root"));

  getchar();  // Wait until user hits "enter"
  mg_stop(ctx);
}
