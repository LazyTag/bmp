#include<map>
#include<vector>
#include<utility>
#include<iostream>
#include<algorithm>
namespace rdm{
	inline long long r(int l,int r){
		return 1ll*rand()*rand()*rand()%(r-l+1)+l;
	}
	template<class I>inline void rarr(I*bg,I*ed,int b){
		for(int *i=bg;i!=ed;i++)*i=i-bg+b;
		random_shuffle(bg,ed);
	}
	struct gph{
		int n,m;
		std::vector<int>a;
		std::vector<std::pair<int,int> >e;
		std::map<std::pair<int,int>,int>h;
		inline void clear(){
			a.clear();e.clear();h.clear();n=m=0;
		}
		inline void build_tree(int x){
			n=x;m=x-1;
			for(int i=2;i<=n;++i){
				x=r(1,i-1);
				e.push_back(std::make_pair(i,x));
				h[e.back()]=h[std::make_pair(x,i)]=1;
			}
			std::random_shuffle(e.begin(),e.end());
		}
		inline void build_list(int x){
			n=x;
			for(int i=1;i<=n;++i)
				e.push_back(std::make_pair(i,0));
			std::random_shuffle(e.begin(),e.end());
			for(int i=0;i<e.size()-1;++i)
				e[i].second=e[i+1].first;
			e.pop_back();
			std::random_shuffle(e.begin(),e.end());
		}
		inline void build_chm(int x){
			n=x;
			for(int i=1,rot=r(1,n);i<=n;++i)
				if(i!=rot)e.push_back(std::make_pair(rot,i));
			std::random_shuffle(e.begin(),e.end());
		}
		inline void build_udg(int x,int y){
			build_tree(x);m=y;
			while(e.size()<m){
				do{x=r(1,n);y=r(1,n);}
				while(x==y||h.find(std::make_pair(x,y))!=h.end());
				e.push_back(std::make_pair(x,y));
				h[e.back()]=h[std::make_pair(y,x)]=1;
			}
			std::random_shuffle(e.begin(),e.end());
		}
		inline void build_dag(int x,int y){
			n=x;m=y;
			for(int i=1;i<=n;++i)
				a.push_back(i);
			std::random_shuffle(a.begin(),a.end());
			for(int i=1;i<a.size();++i){
				e.push_back(std::make_pair(a[r(0,i-1)],a[i]));
				h[e.back()]=1;
			}
			while(e.size()<m){
				do{
					x=r(0,n-1);y=r(0,n-1);if(x>y)std::swap(x,y);
				}while(x==y||h.find(std::make_pair(a[x],a[y]))!=h.end());
				e.push_back(std::make_pair(a[x],a[y]));h[e.back()]=1;
			}
			std::random_shuffle(e.begin(),e.end());
		}
	};
	std::ostream&operator<<(std::ostream&out,gph&x){
		for(int i=0;i<x.e.size();++i)
			out<<x.e[i].first<<' '<<x.e[i].second<<std::endl;
		return out;
	}
}
