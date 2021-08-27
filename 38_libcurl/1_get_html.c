#include<stdio.h>
#include<stdlib.h>
#include<curl/curl.h>
int main()
{
	CURL *curl;
	CURLcode code;
	char url_address[16]="www.baidu.com";
	if(curl = curl_easy_init()){
		curl_easy_setopt(curl,CURLOPT_URL,url_address);
		code = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
	}

	return code;
}
