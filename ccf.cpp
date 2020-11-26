#include<cstdio>
#include<vector>
#include<cstring>
#include<iostream>
#include<windows.h>
namespace BMP{
	std::istream&operator>>(std::istream&in,tagBITMAPFILEHEADER&x){
		char buf[sizeof(tagBITMAPFILEHEADER)]={0};
		int num=fread(buf,1,sizeof(tagBITMAPFILEHEADER),stdin);
		memcpy(&x,buf,sizeof(tagBITMAPFILEHEADER));
		return in;
	}
	std::istream&operator>>(std::istream&in,tagBITMAPINFOHEADER&x){
		char buf[sizeof(tagBITMAPINFOHEADER)]={0};
		fread(buf,1,sizeof(tagBITMAPINFOHEADER),stdin);
		memcpy(&x,buf,sizeof(tagBITMAPINFOHEADER));
		return in;
	}
	std::istream&operator>>(std::istream&in,tagRGBQUAD&x){
		char buf[sizeof(tagRGBQUAD)];
		fread(buf,1,sizeof(tagRGBQUAD),stdin);
		memcpy(&x,buf,sizeof(tagRGBQUAD));
		return in;
	}
	int s[5005][5005];
	#pragma pack(1)
	struct bmp{
		tagBITMAPFILEHEADER h1;
		tagBITMAPINFOHEADER h2;
		std::vector<tagRGBQUAD>rgb;
//		std::vector<>;
//		1 4 8Ë÷Òý
//		16 24 32rgb 
		inline int size_line(){
			int DataSizePerLine=(h2.biWidth*h2.biBitCount+31)/8;
			DataSizePerLine=DataSizePerLine/4*4;
			return DataSizePerLine;
		}
	};
	#pragma pack()
	std::istream&operator>>(std::istream&in,bmp&x){
		in>>x.h1>>x.h2;
		for(int i=0x37;i<=x.h1.bfOffBits;i+=4){
			tagRGBQUAD tmp;in>>tmp;x.rgb.push_back(tmp);
		}
		switch(x.h2.biBitCount){
			case 1:
				for(int k=1,top=0;k<=x.h2.biHeight;++k,top=0)
					for(int i=1;i<=x.size_line();++i){
						unsigned char c;
						fread(&c,1,1,stdin);
						for(int j=7;~j;--j){
							s[k][++top]=(c&(1<<j))?1:0;
//							x.s[k].push_back((c&(1<<j))?1:0);
						}
					}
			break;
			case 4:
			case 8:
			break;
			default:
			break;
		}
		return in;
	}
	std::ostream&operator<<(std::ostream&out,bmp&x){
		for(int k=x.h2.biHeight,top=0;k;--k,top=0){
			for(int i=1;i<=x.size_line();++i)
				for(int j=0;j<8;++j)
					if(s[k][++top]){
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
						out<<(char)20;
					}
					else{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY);
						out<<(char)20;
					}
			out<<std::endl;
		}
		return out;
	}
}
using namespace BMP;
//30*120
int main(){
	freopen("lca.bmp","r",stdin);
//	freopen("demo.out","w",stdout);
	bmp a;
	std::cin>>a;std::cout<<a;
	return 0;
}
