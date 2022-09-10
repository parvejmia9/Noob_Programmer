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

<b> Bitwise Operation:<b>
    </br>
    i)  (a^b)&c =(a&c)^(b&c)

    
    
</br>
<b>Increase Stack Size for Codeblocks</b>
</br>
seetings->compiler->linker settings->other linker-> "-Wl,--stack,1073741824" for 1GB stack size
   ![image](https://user-images.githubusercontent.com/61575111/189493333-84440203-4031-4483-9da3-15db914f7ff6.png)
