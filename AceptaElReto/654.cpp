#include <bits/stdc++.h>
using namespace std;

struct post {
    int minx,maxx,miny,maxy;
};

int main() {
    ios_base::sync_with_stdio(0);cin.tie(0);
    int casos,width,height,x,y,num,id;cin>>casos;
    string line; char a;
    for(;casos--;) {
        unordered_set<char> graph[256];
        post bounds[256];
        char board[200*200];
        unordered_set<char> remaining;
        cin>>width>>height;

        num = 0;
        for(y=0;y<height;y++){
            cin>>line;
            for(x=0;x<width;x++){
                board[y*width+x]=a=line.c_str()[x];
                if(a=='.') continue;
                if(!remaining.count(a)) {
                    bounds[a].minx = bounds[a].maxx = x;
                    bounds[a].miny = bounds[a].maxy = y;
                    remaining.insert(a);
                } else {
                    bounds[a].minx = min(bounds[a].minx, x);
                    bounds[a].maxx = max(bounds[a].maxx, x);
                    bounds[a].maxy = max(bounds[a].maxy, y);
                }
            }
        }

        set<char> front, newfront;
        for(char c : remaining){
            post p = bounds[c];
            bool found = false;
            for(y=p.miny;y<=p.maxy;y++) {
                for(x=p.minx;x<=p.maxx;x++) {
                    a=board[y*width+x];
                    if(a!=c) {
                        graph[c].insert(a);
                        found = true;
                    }
                }
            }
            if(!found) front.insert(c);
        }

        string result = "";
        while(front.size()) {
            newfront = {};
            for(char c : front) remaining.erase(c);
            for(char c : front) {
                result += c;
                result += ' ';
                for(char b : remaining) {
                    graph[b].erase(c);
                    if(!graph[b].size()) newfront.insert(b);
                }
            }
            result.pop_back();
            result += '\n';
            front = newfront;
        }

        if(remaining.size()) printf("IMPOSIBLE\n----\n");
        else printf("%s----\n", result.c_str());
    }

    return 0;
}
