#include <stdio.h>
#include <curl/curl.h>

typedef enum {false=0, true=1, FLASE=0, TRUE=1}bool;
bool getUrl(char *filename)
{
	CURL * curl;
	CURLcode code;
	FILE *fp = NULL;
	if((fp=fopen(filename,"w")) == NULL){
		perror("open file failed");
		return false;
	}
	struct curl_slist *headers=NULL;
	headers = curl_slist_append(headers,"Accept: Agent-007");
	curl = curl_easy_init();
	if(curl){
		curl_easy_setopt(curl,CURLOPT_HTTPHEADER,headers);
		curl_easy_setopt(curl,CURLOPT_URL,"https://www.baidu.com");
		curl_easy_setopt(curl,CURLOPT_WRITEDATA,fp);
		curl_easy_setopt(curl,CURLOPT_HEADERDATA,fp);
		code = curl_easy_perform(curl);
		if(code != 0){
			curl_slist_free_all(headers);
			curl_easy_cleanup(curl);
		}
		fclose(fp);
		return true;
	}
}
bool postUrl(char *filename)
{
    CURL *curl;
    CURLcode res;
    FILE *fp;
    if ((fp = fopen(filename, "w")) == NULL)
        return false;
    curl = curl_easy_init();
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "/tmp/cookie.txt"); // 指定cookie文件
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "&logintype=uid&u=xieyan&psw=xxx86");    // 指定post内容
        //curl_easy_setopt(curl, CURLOPT_PROXY, "10.99.60.201:8080");
        curl_easy_setopt(curl, CURLOPT_URL, " http://mail.sina.com.cn/cgi-bin/login.cgi ");   // 指定url
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
    fclose(fp);
    return true;
}
int main(void)
{
    getUrl("1.html");
    //postUrl("/tmp/post.html");
}
