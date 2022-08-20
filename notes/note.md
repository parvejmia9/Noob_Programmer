<b>Cyle in directed graph</b>
```cpp
vector<int>graph[N];
int cst[N];
int ans;
vector<int>path;
int vis[N];
void dfs(int x){
    vis[x]=1;
    path.push_back(x);
    for(int y:graph[x]){
        if(vis[y]!=2){
            if(vis[y]==0) dfs(y);
            else{
                int mn=1e5;
                int id=path.size()-1;
                while(1){
                    mn=min(mn,cst[path[id]]);
                    if(path[id]==y) break;
                    id--;
                }
                //finding the minimum node cost of each cycle
                ans+=mn;
            }
        }
    }
    path.pop_back();
    vis[x]=2;
}
```
