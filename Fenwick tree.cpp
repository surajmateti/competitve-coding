struct fenwicktree {
vi ft;  
fenwicktree(int n) 
{ 
	ft.assign(n + 1, 0);
}
ll rsq(int b) 
 {
ll sum = 0; 
for (; b; b -= b&-b) sum += ft[b];
return sum;
  }
void update(int k, int v) 
{ 
for (; k < (int)ft.size(); k += k&-k) ft[k] += v;
}
};
