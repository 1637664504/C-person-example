/**
 *	@brief libcurl接收到数据时的回调函数
 *
 *	将接收到的数据保存到本地文件中，同时显示在控制台上。
 *
 *	@param [in] buffer 接收到的数据所在缓冲区
 *	@param [in] size 数据长度
 *	@param [in] nmemb 数据片数量
 *	@param [in/out] 用户自定义指针
 *	@return 获取的数据长度
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

size_t process_data(void *buffer, size_t size, size_t nmemb, void *user_p)
{
	FILE *fp = (FILE *)user_p;
	size_t return_size = fwrite(buffer, size, nmemb, fp);
	//cout << (char *)buffer << endl;
    //printf("buff=%s\n",buffer);
	return return_size;
}

int main(int argc, char **argv)
{
	// 初始化libcurl
	CURLcode return_code;
	return_code = curl_global_init(CURL_GLOBAL_ALL);
	if (CURLE_OK != return_code)
	{
		printf("init libcurl failed.\n");
		return -1;
	}

	// 获取easy handle
	CURL *easy_handle = curl_easy_init();
	if (NULL == easy_handle)
	{
		printf("get a easy handle failed.\n");
        curl_global_cleanup(); 
		return -1;
	}

	FILE *fp = fopen("/dev/null", "w");	// 
	// 设置easy handle属性
	curl_easy_setopt(easy_handle, CURLOPT_URL, "https://www.baidu.com");
	curl_easy_setopt(easy_handle, CURLOPT_WRITEFUNCTION, &process_data);
	curl_easy_setopt(easy_handle, CURLOPT_WRITEDATA, fp);

	// 执行数据请求
	curl_easy_perform(easy_handle);	

    long http_code = 0;
    curl_easy_getinfo (easy_handle, CURLINFO_RESPONSE_CODE, &http_code);
    printf("URL=%s , http_code=%ld\n",argv[1], http_code);

	// 释放资源

	fclose(fp);
	curl_easy_cleanup(easy_handle);
	curl_global_cleanup();

	return 0;
}