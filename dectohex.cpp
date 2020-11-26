#include<queue>
#include<cstdio>
inline void dec_hex(){
	std::queue<unsigned char>q;
	for(unsigned char c;fread(&c,1,1,stdin);)
		for(q.push(c);q.size()==16;putchar('\n'))
			for(;!q.empty();q.pop())
				printf("%02x ",q.front());
	for(;!q.empty();q.pop())
		printf("%02x ",q.front());
}
int main(){
	freopen("demo.bmp","r",stdin);
	freopen("hex.out","w",stdout);
	dec_hex();
	return 0;
}
