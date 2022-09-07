<b>Cyle in Directed Graph:</b>
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
<b>Last Index Checking:</b>
</br>
</br>
let somwhere this loop has executed</br>
```cpp
for(int i=0;i<n-1;i++){
    //something
}
```
*** please check if a[n-1] has any significance to the answer.
