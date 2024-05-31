#include <iostream>
#include "sm4.h"



void test()
{
		
	std::string key = "XXXXX*y@%XXXXXXX";
	std::string data = "helloworldhelloworldhelloworldhelloworldhelloworld";

    sm4 s;
    s.setType(sm4::ECB);
    s.setKey(key);
    s.setIv(key);

    //加密之后再解密
    std::string result = s.encrypt(data);
	
	for (int i = 0; i < result.size(); i++)
	{
		//std::cout << std::hex << (int)result[i];
		printf("%02x", (unsigned char)result[i]);
	}

    //std::cout << s.decrypt(s.encrypt(data)) << std::endl;

    //ECB模式同上, 只是不需要设置IV

	
}

int main(int argc, char* argv[]) 
{
	
	if (argc < 3)
	{
		std::cout << "[only support ECB] usage: sm4.exe -e|-d $key $data" << std::endl;
		
	}

	std::string mode = argv[1];
	std::string key = argv[2];
	std::string data = argv[3];
	
    sm4 s;
    s.setType(sm4::ECB);
    s.setKey(key);
    s.setIv(key);

	
	if(mode == "-e"){
		 std::string result = s.encrypt(data);
	
		for (int i = 0; i < result.size(); i++)
		{
			//std::cout << std::hex << (int)result[i];
			printf("%02x", (unsigned char)result[i]);
		}

	}
	
	if(mode == "-d"){
		
		int size =  data.size()/2;
		char* datarawbuf = new char[size+ 1] ;
		memset(datarawbuf, 0, size+ 1);
		
		const char* pdata = data.c_str();

		for (int i = 0; i < size; i++)
		{
			char tmp[3] = {0};
			strncpy(tmp, &(pdata[i*2]), 2);

			datarawbuf[i] = strtol(tmp, 0, 16);

		}
		
		
		std::string dataraw;
		dataraw.assign(datarawbuf);
		
	
		std::cout << s.decrypt(dataraw) << std::endl;
		
		delete datarawbuf;

	}

    

    return 0;
}