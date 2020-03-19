struct segtree{
  
     vector<int> tree,A,lazy; int N; 
     
    segtree(int n,vector<int> a){
      N=n;
      tree.resize(4*N+5);
      lazy.assign(4*N+5,0);
      A=a;
    }
  
void build(int node, int start, int end)
{
    if(start == end)
    {
        tree[node] = A[start];
    }
    else
    {
        int mid = (start + end) / 2;
     
        build(2*node, start, mid);
        
        build(2*node+1, mid+1, end);
        
        tree[node] = tree[2*node] + tree[2*node+1];
    }
}
void Update(int node, int start, int end, int idx, int val)
{
    if(start == end)
    {
        A[idx] += val;
        tree[node] += val;
    }
    else
    {
        int mid = (start + end) / 2;
        if(start <= idx and idx <= mid)
        {
            
            Update(2*node, start, mid, idx, val);
        }
        else
        {
            
            Update(2*node+1, mid+1, end, idx, val);
        }
        
        tree[node] = tree[2*node] + tree[2*node+1];
    }
}
void updateRange(int node, int start, int end, int l, int r, int val)
{
    if(lazy[node] != 0)
    { 
        
        tree[node] += (end - start + 1) * lazy[node];    
        if(start != end)
        {
            lazy[node*2] += lazy[node];                  
            lazy[node*2+1] += lazy[node];                
        }
        lazy[node] = 0;                                 
    }
    if(start > end or start > r or end < l)             
        return;
    if(start >= l and end <= r)
    {
    
        tree[node] += (end - start + 1) * val;
        if(start != end)
        {
            lazy[node*2] += val;
            lazy[node*2+1] += val;
        }
        return;
    }
    int mid = (start + end) / 2;
    updateRange(node*2, start, mid, l, r, val);        
    updateRange(node*2 + 1, mid + 1, end, l, r, val);   
    tree[node] = tree[node*2] + tree[node*2+1];     
}

ll pquery(int node, int start, int end, int l, int r)
{
    if(start > end or start > r or end < l)
        return 0;         
    if(lazy[node] != 0)
    {

        tree[node] += (end - start + 1) * lazy[node];            
        if(start != end)
        {
            lazy[node*2] += lazy[node];         
            lazy[node*2+1] += lazy[node];    
        }
        lazy[node] = 0;                
    }
    if(start >= l and end <= r)             
        return tree[node];
    int mid = (start + end) / 2;
    ll p1 = pquery(node*2, start, mid, l, r);         
    ll p2 = pquery(node*2 + 1, mid + 1, end, l, r); 
    return (p1 + p2);
}

  void update(int l,int r,int val){

  updateRange(1,0,N-1,l,r,val);

  }
  
  void update(int idx,int val){

  Update(1,0,N-1,idx,val);

  }
  
   ll query(int l,int r){

   return pquery(1,0,N-1,l,r);

   }
 };
