#include<stdio.h>
#include<stdlib.h>
#include<curl/curl.h>
int main()
{
	CURL *curl;
	CURLcode res;
	//char url_address[16]="www.baidu.com";
	char url_address[16]="www.123liuj.com";
	if(curl = curl_easy_init()){
		curl_easy_setopt(curl,CURLOPT_URL,url_address);
		curl_easy_setopt(curl,CURLOPT_INTERFACE,"eth1");
		curl_easy_setopt(curl,CURLOPT_CONNECTTIMEOUT,4);
		res = curl_easy_perform(curl);
		if (res != CURLE_OK)
		{
			switch(res)
			{
				case CURLE_UNSUPPORTED_PROTOCOL:
					fprintf(stderr,"不支持的协议,由URL的头部指定\n");
				case CURLE_COULDNT_CONNECT:
					fprintf(stderr,"不能连接到remote主机或者代理\n");
				case CURLE_HTTP_RETURNED_ERROR:
					fprintf(stderr,"http返回错误\n");
				case CURLE_READ_ERROR:
					fprintf(stderr,"读本地文件错误\n");
				default:
					fprintf(stderr,"返回值:%d\n",res);
			}
			return -1;
		}
		curl_easy_cleanup(curl);
	}

	return res;
}
