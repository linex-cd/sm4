#include <iostream>
#include <cstring>
#include "sm4.h"


// 十六进制转化为int
static int hex2int(char c) {
    if(c >= '0' && c <= '9') {
        return c - '0';
    }else if(c >= 'a' && c <= 'f') {
        return c - 'a' + 10;
    }else if(c >= 'A' && c <= 'F') {
        return c - 'A' + 10;
    }
    return -1;
}

/**
 * 十六进制转化为二进制
 * @param in 十六进制串
 * @param in_len 十六进制串长度，必须为偶数
 * @param out 二进制缓冲区
 */
int hex2bin(const char * in, int in_len, uint8_t * out) {
    int c = 0;
    if((in_len % 2) != 0) {
        return -1;
    }

    while (in_len) {
        if ((c = hex2int(*in++)) < 0) {
            return -1;
        }
        *out = (uint8_t)c << 4;

        if ((c = hex2int(*in++)) < 0) {
            return -1;
        }
        *out |= (uint8_t)c;

        in_len -= 2;
        out++;
    }
    return 1;
}



int main(int argc, char* argv[]) {
	

	/*
	if(argc< 4){
		
		std::cout << "Usage: -e mode{ecb|cbc} iv{char16|-} padding{p5|p7} key{char16} -s{str|file}" << std::endl;
	}
	*/
	
	if(argc< 4){

		std::cout << "Usage: -e|-d key{char16} data{str}" << std::endl;
	}
	
	
	sm4 s;
    s.setType(sm4::ECB);
	
	char *mode = argv[1];
	char *key = argv[2];
	char *iv = argv[2];
	
	char *data = argv[3];
	
    s.setKey(key);
    s.setIv(iv);//ECB模式需要设置IV


    //加密之后再解密
	
	if(strcmp(mode, "-e")==0)
	{
		std::string res = s.encrypt(data);

		const char* p = res.c_str();
		for(int i=0;i<res.length();i++)
		{
			printf("%02x", (uint8_t)p[i]);
		}
	   
		
	}
	if(strcmp(mode, "-d")==0)
	{
			

		uint8_t *out = new uint8_t[strlen(data)];
		
		hex2bin(data, strlen(data), out);
		
		
		
		std::string ret;

		ret.assign(reinterpret_cast<const char*>(out), strlen(data)/2);
		
		std::string res =  s.decrypt(ret);
		

		std::cout << res ;
		
		
	}
	

  
    

    return 0;
}